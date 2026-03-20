#include "Items/Weapons/BulletMaster.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/State/StateMasterComponent.h"
//-----------------------------------------------------------------------------------------------------------
ABulletMaster::ABulletMaster()
{
	//ItemScene = CreateDefaultSubobject<USceneComponent>(TEXT("Item Scene"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	
	//RootComponent = ItemScene;
	//ItemScene->SetupAttachment(RootComponent);
	RootComponent = BoxComponent;
	NiagaraComponent->SetupAttachment(BoxComponent);
	//BoxComponent->SetupAttachment(ItemScene);

	PrimaryActorTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void ABulletMaster::BeginPlay()
{
	Super::BeginPlay();

	if(BoxComponent)
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABulletMaster::OnOverlapBegin);
}
//-----------------------------------------------------------------------------------------------------------
void ABulletMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//-----------------------------------------------------------------------------------------------------------
void ABulletMaster::InitBullet(const FVector& location, const FRotator& rotation, UNiagaraSystem* niagara, TSoftObjectPtr<UNiagaraSystem> bulletHitEffect, const FDamageStruct& damage, AFPSCharacter* playerCharacter)
{
	if(niagara)
		NiagaraComponent->SetAsset(niagara);

	PlayerCharacter = playerCharacter;
	WeaponDamage = damage;
	NiagaraComponent->ResetSystem();
	SetActorLocation(location);
	SetActorRotation(rotation);

	if (!bulletHitEffect.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(bulletHitEffect.ToSoftObjectPath(), [this, bulletHitEffect]()
			{
				if (this)
					BulletHitEffect = bulletHitEffect.Get();
			});
		return;
	}
	BulletHitEffect = bulletHitEffect.Get();

	//ProjectileComponent->Velocity = GetActorForwardVector() * ProjectileComponent->InitialSpeed;
}
//-----------------------------------------------------------------------------------------------------------
void ABulletMaster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterMaster* enemy = nullptr;
	FVector endLocation = {};

	ProjectileComponent->Deactivate();

	BoxComponent->OnComponentBeginOverlap.RemoveAll(this);
	BoxComponent->Deactivate();
	
	WeaponDamage.ImpulseDirection = SweepResult.ImpactNormal;
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), SweepResult.ImpactPoint, SweepResult.ImpactNormal * 100 + SweepResult.ImpactPoint, FLinearColor::Red, 5, 1);
	//UE_LOG(LogTemp, Log, TEXT("Impulse : X=%f, Y=%f, Z=%f"), WeaponDamage.ImpulseDirection.X, WeaponDamage.ImpulseDirection.Y, WeaponDamage.ImpulseDirection.Z)
	if (BulletHitEffect)
	{
		NiagaraComponent->SetAsset(BulletHitEffect);
		NiagaraComponent->ResetSystem();
		NiagaraComponent->OnSystemFinished.AddDynamic(this, &ABulletMaster::DestroyBullet);
		NiagaraComponent->SetWorldRotation(WeaponDamage.ImpulseDirection.Rotation());
	}
	else
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]() { Destroy(); });

	enemy = Cast<ACharacterMaster>(OtherActor);
	if (!enemy)		
		return;
	
	enemy->DealDamage(WeaponDamage, SweepResult);

	UEventBus::OnHitEnemyWidgetAnim.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
void ABulletMaster::DestroyBullet(UNiagaraComponent* PSystem)
{
	Destroy();
}
//-----------------------------------------------------------------------------------------------------------
