#include "Items/Weapons/WeaponMaster.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/StorageComponent.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Items/Weapons/MagazineMaster.h"
#include "Items/Weapons/BulletMaster.h"
#include "Struct/DamageStruct.h"
#include "Config/AudusMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
AWeaponMaster::AWeaponMaster()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));

	RootComponent = ItemScene;
	SkeletalMeshComponent->SetupAttachment(ItemScene);
	ArrowComponent->SetupAttachment(SkeletalMeshComponent);
	NiagaraComponent->SetupAttachment(SkeletalMeshComponent);

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	Tags.Add(FName("Weapon"));
	bIsReloading = false;
	bIsFireCoolDown = false;
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UWeaponMasterDA* weaponDA = GetConfigDA<UWeaponMasterDA>();
	if (!weaponDA || !weaponDA->SkeletalMesh.LoadSynchronous())
		return;

	SkeletalMeshComponent->SetSkeletalMesh(weaponDA->SkeletalMesh.Get());
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::BeginPlay()
{
	Super::BeginPlay();
	InitParams();
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	UEventBus::OnWeaponFire.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::InitParams(UItemMasterDA* ItemDA)
{
	if (WeaponDA)
		return;

	Super::InitParams(ItemDA);
	WeaponDA = GetConfigDA<UWeaponMasterDA>();

	if (WeaponDA)
	{
		if (WeaponDA->SkeletalMesh.Get())
			SkeletalMeshComponent->SetSkeletalMesh(WeaponDA->SkeletalMesh.Get());
		else
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(WeaponDA->SkeletalMesh.ToSoftObjectPath(), [this]()
				{
					if (!WeaponDA->SkeletalMesh.LoadSynchronous())
					{
						AsyncTask(ENamedThreads::GameThread, [this]()
							{
								ALARM_LOG
								Destroy();
							});
						return;
					}
					SkeletalMeshComponent->SetSkeletalMesh(WeaponDA->SkeletalMesh.Get());
				});
		}
		SkeletalMeshComponent->SetSimulatePhysics(true);
	}
	else
	{
		ALARM_LOG
		Destroy();
	}
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::InitParamsActiveWeapon(USkeletalMeshComponent* PlayerSkeletalMesh, int32 ItemLevel, UEquipmentComponent* Component)
{
	if (!WeaponDA)
	{
		WeaponDA = GetConfigDA<UWeaponMasterDA>();
		CHECK_PTR(WeaponDA)
	}

	UEventBus::OnWeaponFire.BindUObject(this, &AWeaponMaster::Fire);

	if (!AnimationShoot)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(WeaponDA->AnimationShoot.ToSoftObjectPath(), [this]() 
			{
				if(WeaponDA->AnimationShoot.ToSoftObjectPath().ResolveObject())
					AnimationShoot = WeaponDA->AnimationShoot.Get();
			});
	}

	EquipmentComponent = Component;

	if (EquipmentComponent)
		MagazineDA = EquipmentComponent->GetActiveMagazine().MagazineDA;

	WeaponLevel = ItemLevel;
	SkeletalMeshComponent->SetSimulatePhysics(false);
	SkeletalMeshComponent->SetCastShadow(false);		
	AttachToComponent(PlayerSkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponDA->SocketName);

	if (NiagaraComponent)
		NiagaraComponent->SetAsset(WeaponDA->WeaponEffect);
	

	DamageStruct.DamageOwner = EquipmentComponent->GetOwner();
	DamageStruct.DamageOwnerComponent = EquipmentComponent->GetOwner()->FindComponentByClass<UStateMasterComponent>();

	/*GetWorld()->GetTimerManager().SetTimer(MoveBulletsTimer, this, &AWeaponMaster::MoveBullets, BulletMoveInterval, true);*/
}
//-----------------------------------------------------------------------------------------------------------
FDamageStruct& AWeaponMaster::GetWeaponDamage()
{
	float magazineDamage = 0.0f;
	float audusDamage = 0.0f;
	UAudusMasterDA* currentAudusDA = nullptr;

	if (!EquipmentComponent)
	{
		ALARM_LOG
		return DamageStruct;
	}
	if (!WeaponDA)
	{
		WeaponDA = GetConfigDA<UWeaponMasterDA>();
		if (!WeaponDA)
		{
			ALARM_LOG
			return DamageStruct;
		}
	}

	currentAudusDA = Cast<UAudusMasterDA>(EquipmentComponent->GetActiveAudus().ItemDA);
	currentAudusDA ? audusDamage = EquipmentComponent->GetActiveAudus().GetItemDamageFromLevel().GetValueFromRange() : audusDamage = 0.0f;

	magazineDamage = MagazineDA->Damage.GetValueFromRange();

	DamageStruct.Damage = EquipmentComponent->GetActiveWeapon().GetItemDamageFromLevel().GetValueFromRange() + magazineDamage + audusDamage;
	DamageStruct.Element1 = WeaponDA->ElementType;

	if (PlayerCharacter && PlayerCharacter->GetStateComponent())
		DamageStruct.ElementChanse = PlayerCharacter->GetStateComponent()->FindElementChanseFromElement(WeaponDA->ElementType);

	return DamageStruct;
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::StartReload(bool Reloading)
{
	Reloading = true;

	if (!WeaponDA)
	{
		WeaponDA = GetConfigDA<UWeaponMasterDA>();
		CHECK_PTR(WeaponDA)
	}
	
	CHECK_PTR(SkeletalMeshComponent)
	CHECK_PTR(SkeletalMeshComponent->GetAnimInstance())

	SkeletalMeshComponent->GetAnimInstance()->Montage_Play(WeaponDA->AnimationWeaponReload);
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::WeaponReload(UEquipmentComponent* Component)
{
	CHECK_PTR(Component)

	EquipmentComponent = Component;	
}
//-----------------------------------------------------------------------------------------------------------
// Логика стрельбы оружием
void AWeaponMaster::Fire(AFPSCharacter* Character)
{
	if (bIsReloading || bIsFireCoolDown)
		return;

	CHECK_PTR(EquipmentComponent)

	if (EquipmentComponent->GetActiveMagazine().CurrentAmmo <= 0 || !EquipmentComponent->GetActiveMagazine().MagazineDA)
	{
		EquipmentComponent->ReloadMagazine();
		return;
	}
		
	if (!WeaponDA)
	{
		WeaponDA = GetConfigDA<UWeaponMasterDA>();
		CHECK_PTR(WeaponDA)
	}
	if (!PlayerCharacter)
	{
		PlayerCharacter = Character;
		if (!PlayerCharacter)
		{
			ALARM_LOG
			return;
		}
	}
	if (!World)
	{
		World = GetWorld();
		CHECK_PTR(World)
	}

	UAudusMasterDA* currentAudusDA = nullptr;
	float weaponSpeed = WeaponDA->AttackSpeed;
	FTimerHandle timerHandle;

	bIsAttack = true;

	if (EquipmentComponent->GetActiveAudus().bOccupied)
	{
		currentAudusDA = Cast<UAudusMasterDA>(EquipmentComponent->GetActiveAudus().ItemDA);
		if (currentAudusDA)
			weaponSpeed = currentAudusDA->AttackSpeed;
	}
	
	SpawnBullet(currentAudusDA);
	bIsFireCoolDown = true;
	World->GetTimerManager().SetTimer(timerHandle, [this]()
		{
			bIsFireCoolDown = false;
			bIsAttack = false;
		}, weaponSpeed, false);
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::SetbIsMeleeAttack(UAnimMontage* Montage, bool bInterrupted)
{
	this->bIsMeleeAttack = false;
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::SpawnBullet(UAudusMasterDA* audusDA)
{
	EFiringMode firingMode;

	if (bIsReloading)
		return;
	
	CHECK_PTR(PlayerCharacter)
	CHECK_PTR(EquipmentComponent)

	if (!WeaponDA)
	{
		WeaponDA = GetConfigDA<UWeaponMasterDA>();
		CHECK_PTR(WeaponDA)
	}
	if (!CameraComponent)
	{
		CameraComponent = PlayerCharacter->GetCameraComponent();
		CHECK_PTR(CameraComponent)
	}
	if (!AnimInstance)
	{
		if (PlayerCharacter && PlayerCharacter->GetMesh1P() && IsValid(PlayerCharacter->GetMesh1P()->GetAnimInstance()))
			AnimInstance = PlayerCharacter->GetMesh1P()->GetAnimInstance();
	}

	FMagazine& magazine = EquipmentComponent->GetActiveMagazine();
	CHECK_PTR(magazine.MagazineDA)

	MagazineDA = magazine.MagazineDA;
	audusDA ? firingMode = audusDA->FiringMode : firingMode = WeaponDA->FiringMode;

	if (AnimationShoot && AnimInstance)
		AnimInstance->Montage_Play(AnimationShoot);

	switch (firingMode)
	{
	case EFiringMode::Auto :
		FireAutoOrSnipe<1.0f>(magazine, audusDA);
		break;
	case EFiringMode::ShotGun :
		FireShotGun(magazine, audusDA);
		break;
	case EFiringMode::Snipe :
		FireAutoOrSnipe<1.33f>(magazine, audusDA);
		break;

	
	default:
		break;
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), WeaponDA->ShootSound);
	UEventBus::OnUpdateAmmoWidget.ExecuteIfBound(magazine.CurrentAmmo, WeaponDA->UseValue);
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::FireShotGun(FMagazine& magazine, UAudusMasterDA* audusDA)
{
	ABulletMaster* bullet = nullptr;
	int32 projectileCount = 10;
	float distanceRadius = 180.0f;
	FVector startLocation = {};
	FVector start = {};
	FVector target = {};
	FVector spread = {};
	FRotator rotation = {};
	FActorSpawnParameters spawnParams = {};
	TArray<FVector> randomPoints = {};

	CHECK_PTR(MagazineDA)

	startLocation = CameraComponent->GetComponentLocation();
	target = CameraComponent->GetForwardVector() * 2000.0f + startLocation;

	start = ArrowComponent->GetComponentLocation();
	if (magazine.CurrentAmmo < projectileCount)
		projectileCount = magazine.CurrentAmmo;

	for (int32 i = 0; i < projectileCount; i++)
	{
		spread = UKismetMathLibrary::RandomPointInBoundingBox(target, FVector(distanceRadius, distanceRadius, distanceRadius));

		randomPoints.Add(spread);
	}

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (const FVector& item : randomPoints)
	{
		rotation = FRotationMatrix::MakeFromX(item - start).Rotator();

		bullet = GetWorld()->SpawnActor<ABulletMaster>(MagazineDA->BulletClass, start, rotation, spawnParams);
		if (!bullet)
			continue;

		bullet->InitBullet(start, rotation, WeaponDA->BulletEffect, WeaponDA->BulletHitEffect, GetWeaponDamage(), PlayerCharacter);
	}
	
	magazine.CurrentAmmo -= projectileCount;
}
//-----------------------------------------------------------------------------------------------------------
template<float valueScale>
inline void AWeaponMaster::FireAutoOrSnipe(FMagazine& magazine, UAudusMasterDA* audusDA)
{
	ABulletMaster* bullet = nullptr;
	float distance = 0.0f;
	float distanceRadius = 0.0f;
	FVector startLocation = {};
	FVector endLocation = {};
	FVector start = {};
	FVector target = {};
	FVector sizeScale = {};
	FHitResult hitResult = {};
	FRotator rotation = {};
	FActorSpawnParameters spawnParams = {};
	FCollisionQueryParams traceParams(FName(TEXT("WeaponTrace")), false, this);
	TArray<AActor*> ignores = {};

	startLocation = CameraComponent->GetComponentLocation();
	endLocation = CameraComponent->GetForwardVector() * 19999.0f + startLocation;

	UKismetSystemLibrary::LineTraceSingle(this, startLocation, endLocation, ETraceTypeQuery::TraceTypeQuery3, false, ignores,
		EDrawDebugTrace::None, hitResult, true);

	start = ArrowComponent->GetComponentLocation(); // SkeletalMeshComponent->GetSocketLocation(WeaponDA->SocketBullet);

	if (hitResult.IsValidBlockingHit())
		target = hitResult.Location;
	else
		target = hitResult.TraceEnd;

	distance = FVector::Distance(startLocation, target);
	if (distance <= 275.0f)
		target = CameraComponent->GetForwardVector() * 999.0f + startLocation;;

	//Тестовый разброс пуль
	distance = FVector::Distance(start, target);
	while (distance >= 0.0f)
	{
		distanceRadius += 1.25f;
		distance -= 100.0f;
	}
	FVector spread = UKismetMathLibrary::RandomPointInBoundingBox(target, FVector(distanceRadius, distanceRadius, distanceRadius));

	rotation = FRotationMatrix::MakeFromX(spread - start).Rotator();

	CHECK_PTR(MagazineDA)

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	bullet = GetWorld()->SpawnActor<ABulletMaster>(MagazineDA->BulletClass, start, rotation, spawnParams);
	CHECK_PTR(bullet)

	PTR(bullet->ProjectileComponent)->InitialSpeed *= valueScale;
	bullet->ProjectileComponent->MaxSpeed *= valueScale;
	bullet->ProjectileComponent->ProjectileGravityScale /= valueScale;

	CHECK_PTR(bullet->BoxComponent)

	sizeScale = bullet->BoxComponent->GetComponentScale();

	sizeScale.X *= valueScale;
	sizeScale.Y *= valueScale;
	sizeScale.Z *= valueScale;

	bullet->BoxComponent->SetWorldScale3D(sizeScale);

	bullet->InitBullet(start, rotation, WeaponDA->BulletEffect, WeaponDA->BulletHitEffect, GetWeaponDamage(), PlayerCharacter);

	magazine.CurrentAmmo -= 1;

}
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------
//void AWeaponMaster::MoveBullets()
//{
//	bool bIsHit = false;
//	ACharacterMaster* LocalEnemy = nullptr;
//	UNiagaraComponent* LocalNiagaraComponent = nullptr;
//	FHitResult LocalHitResult = {};
//	FVector LocalEndLocation = {};
//	FDamageStruct LocalDamageStruct = {};
//
//	for (int32 i = BulletsForSpawn.Num() - 1; i >= 0; --i)
//	{
//		LocalEndLocation = BulletsForSpawn[i].Location + BulletsForSpawn[i].Direction * 175.0;
//		bIsHit = GetWorld()->LineTraceSingleByChannel(LocalHitResult, BulletsForSpawn[i].Location, LocalEndLocation, ECollisionChannel::ECC_Visibility);
//		//DrawDebugLine(GetWorld(), BulletsForSpawn[i].Location, LocalEndLocation, FColor::Red, false, 0.2, 0, 0.5);
//
//		if (bIsHit && LocalHitResult.GetComponent()->ComponentHasTag(FName(TEXT("BulletTarget"))))
//		{
//			LocalEnemy = Cast<ACharacterMaster>(LocalHitResult.GetActor());
//			if (LocalEnemy)
//			{
//				LocalDamageStruct = GetWeaponDamage();
//				LocalDamageStruct.ImpulseDirection = (LocalHitResult.Location - BulletsForSpawn[i].Location).GetSafeNormal();
//				LocalEnemy->DealDamage(LocalDamageStruct, LocalHitResult);
//				if (PlayerCharacter)
//					PlayerCharacter->PlayHitEnemyAnimation();
//			}
//			
//			BulletsForSpawn.RemoveAt(i);
//			continue;
//		}
//
//		--BulletsForSpawn[i].MoveBulletCount;
//		if (BulletsForSpawn[i].MoveBulletCount <= 0)
//		{
//			BulletsForSpawn.RemoveAt(i);
//			continue;
//		}
//
//		BulletsForSpawn[i].Location = LocalEndLocation;
//
//		CHECK_PTR(MagazineDA)
//		if (MagazineDA->BulletEffect)
//		{
//			LocalNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MagazineDA->BulletEffect, LocalEndLocation, BulletsForSpawn[i].Rotation, FVector(1.0, 1.0, 1.0));
//			CHECK_PTR(LocalNiagaraComponent)
//
//			LocalNiagaraComponent->SetVariableLinearColor(FName(TEXT("Color")), BulletColor);
//		}
//	}
//}
//-----------------------------------------------------------------------------------------------------------
