#include "SkillActors/LightningWallSA.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Character/CharacterMaster.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
ALightningWallSA::ALightningWallSA()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	BoxComponent->SetupAttachment(RootComponent);
}
//-----------------------------------------------------------------------------------------------------------
void ALightningWallSA::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void ALightningWallSA::SphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	FVector niagaraSize(1.0f);

	CollisionSphereComponent->Deactivate();
	CollisionSphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	ProjectileComponent->StopMovementImmediately();
	ProjectileComponent->ProjectileGravityScale = 0.0f;

	SkillDealDamage();
	GetWorld()->GetTimerManager().SetTimer(DamageTimer, this, &ALightningWallSA::SkillDealDamage, 0.33f, true);

	UGameplayStatics::PlaySoundAtLocation(this, ScrollDA->EndSound, GetActorLocation());

	if (!ScrollDA->ExplodeNiagara.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(ScrollDA->ExplodeNiagara.ToSoftObjectPath(), [&, niagaraSize]()
			{
				AsyncTask(ENamedThreads::GameThread, [&, niagaraSize]()
					{
						CHECK_PTR(ScrollDA)

							ApplyNiagaraParameters(ScrollDA->ExplodeNiagara.Get(), niagaraSize);
					});
			});
		return;
	}

	ApplyNiagaraParameters(ScrollDA->ExplodeNiagara.Get(), niagaraSize);
}
//-----------------------------------------------------------------------------------------------------------
void ALightningWallSA::InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner)
{
	Super::InitParam(scrollDA, elementChance, owner);

	CHECK_PTR(ScrollDA)

	FVector niagaraSize(0.09f);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightningWallSA::BoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALightningWallSA::BoxEndOverlap);

	if (!ScrollDA->ProjectileNiagara.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(ScrollDA->ProjectileNiagara.ToSoftObjectPath(), [&]()
			{
				AsyncTask(ENamedThreads::GameThread, [&]()
					{
						CHECK_PTR(ScrollDA)

						ApplyNiagaraParameters(ScrollDA->ProjectileNiagara.Get(), niagaraSize);
					});
			});
		return;
	}

	ApplyNiagaraParameters(ScrollDA->ProjectileNiagara.Get(), niagaraSize);
}
//-----------------------------------------------------------------------------------------------------------
void ALightningWallSA::SkillDealDamage()
{
	CHECK_PTR(ScrollDA)

	if (!NiagaraComponent->IsActive())
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimer);
		BoxComponent->Deactivate();

		for (ACharacterMaster* item : Characters)
		{
			if (!item)
				continue;

			item->CustomTimeDilation = 1.0f;
		}

		Destroy();
		return;
	}

	DamageStruct.Element1 = ScrollDA->SkillElement1;
	DamageStruct.ElementChanse = ElementChance;

	for (ACharacterMaster* item : Characters)
	{
		if (!item)
			continue;

		DamageStruct.Damage = ScrollDA->SkillAttackDamage.GetValueFromRange();
		item->DealDamage(DamageStruct);
	}
}
//-----------------------------------------------------------------------------------------------------------
void ALightningWallSA::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterMaster* character = nullptr;
	OtherActor->CustomTimeDilation = 0.55f;

	character = Cast<ACharacterMaster>(OtherActor);
	CHECK_PTR(character)

	Characters.Add(character);
}
//-----------------------------------------------------------------------------------------------------------
void ALightningWallSA::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterMaster* character = nullptr;
	int32 index = 0;
	OtherActor->CustomTimeDilation = 1.0f;

	character = Cast<ACharacterMaster>(OtherActor);
	CHECK_PTR(character)
		
	if(Characters.Find(character, index))
		Characters[index] = nullptr;
}
//-----------------------------------------------------------------------------------------------------------