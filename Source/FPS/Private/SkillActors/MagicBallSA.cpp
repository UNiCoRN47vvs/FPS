#include "SkillActors/MagicBallSA.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Character/CharacterMaster.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
void AMagicBallSA::InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner)
{
	Super::InitParam(scrollDA, elementChance, owner);

	if (!ScrollDA)
	{
		ALARM_LOG
			Destroy();
		return;
	}

	if (ScrollDA->ProjectileNiagara.Get())
		ApplyNiagaraParameters(ScrollDA->ProjectileNiagara.Get(), FVector(1.0f));
	else
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(ScrollDA->ProjectileNiagara.ToSoftObjectPath(), [&]()
			{
				AsyncTask(ENamedThreads::GameThread, [&]()
					{
						ApplyNiagaraParameters(ScrollDA->ProjectileNiagara.Get(), FVector(1.0f));
					});
			});
	}
}
//-----------------------------------------------------------------------------------------------------------
void AMagicBallSA::SphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	CollisionSphereComponent->Deactivate();
	CollisionSphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	ProjectileComponent->StopMovementImmediately();
	ProjectileComponent->ProjectileGravityScale = 0.0f;
	ApplyMagicBallDamage();
}
//-----------------------------------------------------------------------------------------------------------
void AMagicBallSA::ApplyMagicBallDamage()
{
	CHECK_PTR(ScrollDA)

	if (!ScrollDA->ExplodeNiagara.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(ScrollDA->ExplodeNiagara.ToSoftObjectPath(), [this]()
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						ApplyMagicBallDamage();
					});
			});
		return;
	}

	bool bIsHit = false;
	int32 index = 0;
	float sphereRadius = 350.0f;
	AActor* enemyActor = nullptr;
	ACharacterMaster* enemyCharacter = nullptr;
	FVector actorLocation = GetActorLocation();
	TArray<AActor*> actorsArray = {};
	TArray<FHitResult> outHitResult = {};
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};

	UGameplayStatics::PlaySoundAtLocation(this, ScrollDA->EndSound, GetActorLocation());

	SetActorRotation(FRotator(0.0f));
	PTR(NiagaraComponent)->SetAsset(ScrollDA->ExplodeNiagara.Get());
	NiagaraComponent->SetWorldScale3D(FVector(1.0f));
	NiagaraComponent->ResetSystem();
	NiagaraComponent->SetVariableLinearColor(FName(TEXT("Color1")), ScrollDA->SkillColor);
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AMagicBallSA::DestroyAfterNiagara);

	objectType.Add(EObjectTypeQuery::ObjectTypeQuery9);

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this, actorLocation, actorLocation, sphereRadius,
		objectType, true, actorsArray, EDrawDebugTrace::None, outHitResult, true);

	if (!bIsHit)
		return;

	DamageStruct.Element1 = ScrollDA->SkillElement1;
	DamageStruct.ElementChanse = ElementChance;

	for (const FHitResult& item : outHitResult)
	{
		enemyActor = item.GetActor();

		if (actorsArray.Find(enemyActor, index))
			continue;

		enemyCharacter = Cast<ACharacterMaster>(enemyActor);
		if (!enemyCharacter)
			continue;
		DamageStruct.Damage = ScrollDA->SkillAttackDamage.GetValueFromRange();
		enemyCharacter->DealDamage(DamageStruct, item);

		actorsArray.Add(enemyActor);
	}
}
//-----------------------------------------------------------------------------------------------------------