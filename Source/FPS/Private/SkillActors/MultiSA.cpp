#include "SkillActors/MultiSA.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemies/EnemyMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Struct/DamageStruct.h"
#include "Config/EnemyMasterDA.h"
#include "Config/SkillAttackDA.h"
//-----------------------------------------------------------------------------------------------------------
AMultiSA::AMultiSA()
{
	RootComponent = NiagaraComponent;
}
//-----------------------------------------------------------------------------------------------------------
void AMultiSA::ActivateSkill()
{
	SkillIndex = FMath::RandRange(0, SkillsDA.Num() - 1);

	USkillMasterDA* skillDA = SkillsDA[SkillIndex];

	CHECK_PTR(skillDA)
		CHECK_PTR(EnemyDA)

		if (!skillDA->SkillEffect.IsValidIndex(0))
			return;
	if (!skillDA->SkillEffect.IsValidIndex(1))
		return;

	CHECK_PTR(skillDA->SkillEffect[0])
		CHECK_PTR(skillDA->SkillEffect[1])

	bool bIsHit = false;
	float radius = EnemyDA->AttackDistance * 10;
	FVector location = GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
	TArray<AActor*> ignoreActors = {};
	TArray<FHitResult> outHitResult = {};

	objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this, location, location, radius, objectType, false, ignoreActors, EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 1.0);

	if (!bIsHit)
	{
		DestroyAfterNiagara(nullptr);
		return;
	}
	
	for (auto& item : outHitResult)
	{
		if (item.GetActor()->ActorHasTag(FName(TEXT("Player"))))
		{
			PlayerLocation = item.GetActor()->GetActorLocation();
			PlayerLocation.Z -= 90.0;
			break;
		}
	}

	SetActorLocation(PlayerLocation);

	NiagaraComponent->SetAsset(skillDA->SkillEffect[0]);
	NiagaraComponent->ResetSystem();
	NiagaraComponent->SetColorParameter(FName("Color"), skillDA->SkillEffectColor[0]);

	NiagaraComponent->OnSystemFinished.RemoveAll(this);
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AMultiSA::MultiStep2);
}
//-----------------------------------------------------------------------------------------------------------
void AMultiSA::MultiStep2(UNiagaraComponent* finishedComponent)
{
	USkillMasterDA* enemySkillDA = SkillsDA[SkillIndex];

	CHECK_PTR(enemySkillDA)
	CHECK_PTR(finishedComponent)
	CHECK_PTR(EnemyDA)

	bool bIsHit = false;
	float radius = 0.0f;
	ACharacterMaster* character = nullptr;
	UNiagaraSystem* skillEffect = nullptr;
	UNiagaraComponent* niagaraComponent = nullptr;
	USkillAttackDA* skillDA = nullptr;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
	TArray<AActor*> ignoreActors = {};
	TArray<FHitResult> outHitResult = {};

	skillEffect = enemySkillDA->SkillEffect[1];

	CHECK_PTR(skillEffect)

	NiagaraComponent->SetAsset(skillEffect);
	NiagaraComponent->ResetSystem();
	NiagaraComponent->SetColorParameter(FName("Color"), enemySkillDA->SkillEffectColor[1]);

	NiagaraComponent->OnSystemFinished.RemoveAll(this);
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AMultiSA::DestroyAfterNiagara);

	radius = EnemyDA->AttackSphereRadius;
	objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this, PlayerLocation, PlayerLocation, radius, objectType, false, ignoreActors,
		EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 1.0);

	if (!bIsHit)
		return;

	CHECK_PTR(EnemyCharacter)
	CHECK_PTR(EnemyCharacter->GetStateComponent())

	for (const FHitResult& item : outHitResult)
	{
		if (item.GetActor()->ActorHasTag(FName(TEXT("Player"))))
		{
			character = Cast<ACharacterMaster>(item.GetActor());
			skillDA = Cast<USkillAttackDA>(enemySkillDA);
			CHECK_PTR(character)
				CHECK_PTR(skillDA)

				DamageStruct.Damage = skillDA->SkillAttackDamage.GetValueFromRange() + EnemyDA->EnemyAttackDamage.GetValueFromRange();
			DamageStruct.Element1 = skillDA->SkillElement1;
			DamageStruct.ElementChanse = EnemyCharacter->GetStateComponent()->FindElementChanseFromElement(skillDA->SkillElement1);
			character->DealDamage(DamageStruct);
			break;
		}
	}

}
//-----------------------------------------------------------------------------------------------------------