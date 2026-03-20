#include "ActorComponents/State/EnemyStateComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enemies/EnemyMaster.h"
#include "Config/SkillDefenseDA.h"
//-----------------------------------------------------------------------------------------------------------
UEnemyStateComponent::UEnemyStateComponent()
{
	CheckInterval = 1.0;
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (AuraSkill.NiagaraComponent)
		AuraSkill.NiagaraComponent->DestroyComponent();

	if (DefenseSkill.NiagaraComponent)
		DefenseSkill.NiagaraComponent->DestroyComponent();

}
//-----------------------------------------------------------------------------------------------------------
AEnemyMaster* UEnemyStateComponent::GetEnemyOwner()
{
	if (!EnemyCharacter)
		EnemyCharacter = Cast<AEnemyMaster>(GetOwner());
	return EnemyCharacter;
}
//-----------------------------------------------------------------------------------------------------------
bool UEnemyStateComponent::IsDefenseSkillActive()
{
	if(!GetWorld()->GetTimerManager().TimerExists(BuffTimer))
		return false;

	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::UseDefenseSkill(UNiagaraComponent* NiagaraComponent, USkillDefenseDA* SkillDA)
{
	if (GetWorld()->GetTimerManager().TimerExists(BuffTimer))
		return;

	switch (SkillDA->SkillStateName)
	{
	case EStateName::Health:		
	case EStateName::Stamina:
		AuraSkill.LifeTime = SkillDA->LifeTime;
		AuraSkill.NiagaraComponent = NiagaraComponent;
		AuraSkill.SkillDA = SkillDA;
		break;

	default:
		DefenseSkill.LifeTime = SkillDA->LifeTime;
		DefenseSkill.NiagaraComponent = NiagaraComponent;
		DefenseSkill.SkillDA = SkillDA;
		break;
	}

	ApplyDefenseSkill(SkillDA);
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::ApplyDefenseSkill(USkillDefenseDA* SkillDA)
{
	EStateName stateName = SkillDA->SkillStateName;

	GetWorld()->GetTimerManager().SetTimer(BuffTimer, this, &UEnemyStateComponent::ApplySkillBuff, CheckInterval, true);

	switch (stateName)
	{
	case EStateName::Health:
	case EStateName::Stamina:
		return;
		break;
	default:
		if (StateMap.Contains(stateName))
			*StateMap.Find(stateName) += DefenseSkill.SkillDA->SkillPercent;
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::ApplyStateAura(bool bIsActiveAura)
{
	if (!bIsActiveAura)
	{
		AuraSkill.NiagaraComponent->DestroyComponent();
		return;
	}
	bool bIsHit = false;
	float radius = 500.0f;
	UStateMasterComponent* stateComponent = nullptr;
	FVector location = GetEnemyOwner()->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
	TArray<AActor*> ignoreActors = {};
	TArray<FHitResult> outHitResult = {};
	objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this, location, location, radius, objectType, false,
		ignoreActors, EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 1.0);

	if (!bIsHit)
		return;

	for(const FHitResult& item : outHitResult)
	{ 
		stateComponent = item.GetActor()->FindComponentByClass<UStateMasterComponent>();
		if (!stateComponent)
		{
			ALARM_LOG
			continue;
		}
		stateComponent->AuraEffect(AuraSkill.SkillDA.Get());
	}
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::ApplySkillBuff()
{
		if (!GetEnemyOwner() || DefenseSkill.LifeTime <= 0.0 && AuraSkill.LifeTime <= 0.0)
		{
			GetWorld()->GetTimerManager().ClearTimer(BuffTimer);
			return;
		}

		if (DefenseSkill.LifeTime > 0.0)
		{
			DefenseSkill.LifeTime -= CheckInterval;
			if (DefenseSkill.LifeTime <= 0.0)
			{
				DefenseSkill.NiagaraComponent->DestroyComponent();
				*StateMap.Find(DefenseSkill.SkillDA->SkillStateName) -= DefenseSkill.SkillDA->SkillPercent;
				DefenseSkill.LifeTime = 0.0;
				DefenseSkill.NiagaraComponent = nullptr;
				DefenseSkill.SkillDA = nullptr;
			}
		}

		if (AuraSkill.LifeTime > 0.0)
		{
			AuraSkill.LifeTime -= CheckInterval;
			ApplyStateAura(true);
			if (AuraSkill.LifeTime <= 0.0)
			{
				ApplyStateAura(false);
				AuraSkill.LifeTime = 0.0;
				AuraSkill.NiagaraComponent = nullptr;
				AuraSkill.SkillDA = nullptr;
			}
		}		
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::AuraEffect(USkillDefenseDA* SkillDA)
{
	Super::AuraEffect(SkillDA);
	CHECK_PTR(SkillDA)

	EStateName stateName = EStateName::Health;
	switch (SkillDA->SkillStateName)
	{
	case EStateName::Health:
		stateName = EStateName::Health;
		break;

	case EStateName::Stamina:
		stateName = EStateName::Stamina;
		break;

	default:
		return;
		break;
	}

	if (!StateMap.Contains(stateName))
		return;

	*StateMap.Find(stateName) += SkillDA->SkillPercent; //TODO : »«менить на функцию отхила
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateComponent::SetEnemyStateMap(const TMap<EStateName, float>& enemyStateMap)
{
	StateMap = enemyStateMap;
}
