#include "ActorComponents/State/StateMasterComponent.h"
#include "Engine/DataTable.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "SubSystem/StatDataSubsystem.h"
#include "SubSystem/WorldRuler.h"
#include "FPS/FPSGameMode.h"
#include "StatObjects/StatObjectMaster.h"
#include "FPS/FPSCharacter.h"
#include "Config/SkillDefenseDA.h"
#include "Struct/DamageStruct.h"
//-----------------------------------------------------------------------------------------------------------
UStateMasterComponent::UStateMasterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsDead = false;
	BuffDebuffTimerTime = 0.5;
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(BuffDebuffTimerHandle, this, &UStateMasterComponent::BuffDebuff, BuffDebuffTimerTime, true);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::BuffDebuff()
{	
	//Cold Effect
	ColdTimerFunc();

	//Poison Effect
	PoisonTimerFunc();

	//Fire Effect
	FireTimerFunc();

	//Physical Effect
	PhysicalTimerFunc();

	//Dilation Up Effect
	DilationUpBuffFunc();
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::InitStateComponent(const FPortalStat& PortalStat)
{
	for (const auto& item : PortalStat.StatsValue.StatsValue)
	{
		IncreaseStateElem(item.Key, item.Value);
		switch (item.Key)
		{
			case EStateName::HealthMax :
				if (StateMap.Contains(EStateName::Health) && StateMap.Contains(EStateName::HealthMax))
					*StateMap.Find(EStateName::Health) = *StateMap.Find(EStateName::HealthMax);
				break;

			case EStateName::StaminaMax :
				if (StateMap.Contains(EStateName::Stamina) && StateMap.Contains(EStateName::StaminaMax))
					*StateMap.Find(EStateName::Stamina) = *StateMap.Find(EStateName::StaminaMax);
				break;

			case EStateName::ManaMax :
				if (StateMap.Contains(EStateName::Mana) && StateMap.Contains(EStateName::ManaMax))
					*StateMap.Find(EStateName::Mana) = *StateMap.Find(EStateName::ManaMax);
				break;

		default:
			break;
		}
	}

	InitSpecificStat();
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::InitSpecificStat()
{
	UStatObjectMaster* statObject = nullptr;
	TSubclassOf<UStatObjectMaster> object = nullptr;

	for (auto item = StateMap.CreateIterator(); item; ++item)
	{
		if (StatObjects.Contains(item->Key))
		{
			statObject = *StatObjects.Find(item->Key);
			if (!statObject)
				continue;

			statObject->InitParams(this, item->Value);
			continue;
		}
		if (!UStatDataSubsystem::StatArray.IsValidIndex(static_cast<int32>(item->Key)))
			continue;

		object = UStatDataSubsystem::StatArray[static_cast<int32>(item->Key)].StatObject;
		if (!object)
			continue;

		statObject = NewObject<UStatObjectMaster>(this, object);
		if (!statObject)
			continue;

		statObject->InitParams(this, item->Value);

		if (UStatDataSubsystem::StatArray[static_cast<int32>(item->Key)].GameplayTag.HasTagExact(AttackTag))
			OnDealDamage.AddUObject(statObject, &UStatObjectMaster::ApplyStatEffect);
		else if (UStatDataSubsystem::StatArray[static_cast<int32>(item->Key)].GameplayTag.HasTagExact(DeffenceTag))
			OnTakeDamage.AddUObject(statObject, &UStatObjectMaster::ApplyStatEffect);

		StatObjects.Add(item->Key, statObject);
	}

	for (auto item = StatObjects.CreateIterator(); item; ++item)
	{
		if (StateMap.Contains(item->Key))
			continue;

		item->Value->DestroyStatObject();
		item.RemoveCurrent();
		continue;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::IncreaseStateElem(EStateName stateName, float value)
{
	if (StateMap.Contains(stateName))
		*StateMap.Find(stateName) += value;
	else
		StateMap.Add(stateName, value);
}
//-----------------------------------------------------------------------------------------------------------
//Getter
float UStateMasterComponent::GetStateMapElem(EStateName stateName)
{
	if (!StateMap.Contains(stateName))
		return 0.0;

	return *StateMap.Find(stateName);
}
TMap<EStateName, float>& UStateMasterComponent::GetStateMap()
{
	return StateMap;
}
FElementsChanse* UStateMasterComponent::GetElementsData(EElementsType ElementType)
{
	TArray<FElementsChanse*> elementsChanceArray = {};
	ElementsDataTable->GetAllRows(FString(TEXT("ElementsDataTable ERROR!")), elementsChanceArray);

	for (FElementsChanse* elem : elementsChanceArray)
	{
		if (!elem)
			continue;

		if (elem->ElementType == ElementType)
			return elem;
	}

	return nullptr;
}
float UStateMasterComponent::GetStateResistance(EElementsType ElementType)
{
	switch (ElementType)
	{
	case EElementsType::None:
		return 0.0;
		break;

	case EElementsType::Physical:
		return GetStateMapElem(EStateName::PhysicalResistance);
		break;

	case EElementsType::Fire:
		return GetStateMapElem(EStateName::FireResistance);
		break;

	case EElementsType::Lightning:
		return GetStateMapElem(EStateName::LightningResistance);
		break;
	case EElementsType::Cold:
		return GetStateMapElem(EStateName::ColdResistance);
		break;
	case EElementsType::Poison:
		return GetStateMapElem(EStateName::PoisonResistance);
		break;
	}
	return 0.0;
}
//-----------------------------------------------------------------------------------------------------------
float UStateMasterComponent::FindElementChanseFromElement(EElementsType elementType)
{
	switch (elementType)
	{
	case EElementsType::Physical:
		return GetStateMapElem(EStateName::PhysicalElementChance);
		break;
	case EElementsType::Fire:
		return GetStateMapElem(EStateName::FireElementChance);
		break;
	case EElementsType::Lightning:
		return GetStateMapElem(EStateName::LightningElementChance);
		break;
	case EElementsType::Cold:
		return GetStateMapElem(EStateName::ColdElementChance);
		break;
	case EElementsType::Poison:
		return GetStateMapElem(EStateName::PoisonElementChance);
		break;
	case EElementsType::None:
	default:
		break;
	}

	return 0.0;
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::RestoreAfterDeath()
{
	if (StateMap.Contains(EStateName::Health) && StateMap.Contains(EStateName::HealthMax))
		*StateMap.Find(EStateName::Health) = *StateMap.Find(EStateName::HealthMax);

	if (StateMap.Contains(EStateName::Stamina) && StateMap.Contains(EStateName::StaminaMax))
		*StateMap.Find(EStateName::Stamina) = *StateMap.Find(EStateName::StaminaMax);

	if (StateMap.Contains(EStateName::Mana) && StateMap.Contains(EStateName::ManaMax))
		*StateMap.Find(EStateName::Mana) = *StateMap.Find(EStateName::ManaMax);

	bIsDead = false;
	PrimaryComponentTick.bCanEverTick = true;

	OnChangeState.Broadcast(EStateName::Health, GetStateMapElem(EStateName::Health), GetStateMapElem(EStateName::HealthMax));
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));
	OnChangeState.Broadcast(EStateName::Mana, GetStateMapElem(EStateName::Mana), GetStateMapElem(EStateName::ManaMax));
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyHeal(float HealPoint)
{
	float healPoint = 0.0f;

	if (GetStateMapElem(EStateName::Health) + HealPoint > GetStateMapElem(EStateName::HealthMax))
		healPoint = GetStateMapElem(EStateName::HealthMax) - GetStateMapElem(EStateName::Health);
	else
		healPoint = HealPoint;

	IncreaseStateElem(EStateName::Health, healPoint);

	if (StateMap.Contains(EStateName::Health) && StateMap.Contains(EStateName::HealthMax))
		OnChangeState.Broadcast(EStateName::Health, *StateMap.Find(EStateName::Health), *StateMap.Find(EStateName::HealthMax));
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyDamage(FDamageStruct& damageStruct)
{
	if (bIsDead || IsBeingDestroyed() || StateMap.Num() <= 0)
		return;

	UStateMasterComponent* damageOwnerComponent = nullptr;
	float* health = StateMap.Find(EStateName::Health);
	IDeathInterface* deathInterface = nullptr;
	CHECK_PTR(health)

	damageStruct.Damage = DamageResistance(damageStruct.Damage, damageStruct.Element1);

	OnTakeDamage.Broadcast(damageStruct);
	if (damageStruct.DamageOwnerComponent)
		damageStruct.DamageOwnerComponent->OnDealDamage.Broadcast(damageStruct);

	if (ElementsDataTable)
		ApplyElementEffect(damageStruct);
	
	if (bIsDead)
		return;

	if (PhysicalEffect.bIsEffect)
	{
		FElementsChanse* elementChanse = GetElementsData(EElementsType::Physical);
		if(elementChanse)
			damageStruct.Damage += FMath::RandRange(elementChanse->ElementalPDMin, elementChanse->ElementalPDMax) / 100.0 * damageStruct.Damage;
	}

	UE_LOG(LogTemp, Warning, TEXT("-[%S]- : Damage = %f"), __FUNCTION__, damageStruct.Damage);
	*health -= damageStruct.Damage;
	OnChangeState.Broadcast(EStateName::Health, GetStateMapElem(EStateName::Health), GetStateMapElem(EStateName::HealthMax));

	CHECK_CAST(CharacterOwner, ACharacterMaster, GetOwner())

	CharacterOwner->HitReaction();
	
	if (*health > 0.6)
		return;

	deathInterface = Cast<IDeathInterface>(GetOwner());
	CHECK_PTR(deathInterface)

	bIsDead = true;
	PrimaryComponentTick.bCanEverTick = false;
	DeathTimerClear();
	deathInterface->ApplyDeath();
	CharacterOwner->GetMesh()->AddImpulse(damageStruct.ImpulseDirection * -1750.0f);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::DeathTimerClear()
{
	OnFireEffect.ExecuteIfBound(false, 0, nullptr);
	OnPhysicalEffect.ExecuteIfBound(false, nullptr);
	OnColdEffect.ExecuteIfBound(false, 0, nullptr);
	OnPoisonEffect.ExecuteIfBound(false, 0, nullptr);
	SandDebuff.CurrentLifeTime = 0.0;
}
//-----------------------------------------------------------------------------------------------------------
float UStateMasterComponent::DamageResistance(float damage, EElementsType firstElement)
{
	float percentResistanse1 = GetStateResistance(firstElement);

	float result1 = damage;

	if (percentResistanse1 > 75.0f) //TODO : Кап резистов, вынести значение!
		percentResistanse1 = 75.0f;

	
	if(percentResistanse1 > 0.0)
		result1 -= percentResistanse1 / 100.0 * damage;

	if (percentResistanse1 < 0.0)
		result1 += -percentResistanse1 / 100.0 * damage;

	return result1;
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyDilationUpBuff(float dilationValueBuff, float dilationTime)
{
	DilationUpBuff.bIsEffect = true;
	DilationUpBuff.DilationValueBuff += dilationValueBuff;
	DilationUpBuff.CurrentLifeTime = dilationTime;

	GetOwner()->CustomTimeDilation += dilationValueBuff;
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::DilationUpBuffFunc()
{
	if (!DilationUpBuff.bIsEffect)
		return;

	DilationUpBuff.CurrentLifeTime -= BuffDebuffTimerTime;

	if (DilationUpBuff.CurrentLifeTime > 0.0)
		return;

	GetOwner()->CustomTimeDilation -= DilationUpBuff.DilationValueBuff;

	DilationUpBuff.bIsEffect = false;
	DilationUpBuff.DilationValueBuff = 0.0;
	DilationUpBuff.CurrentLifeTime = 0.0;
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyElementEffect(const FDamageStruct& damageStruct)
{
	if (damageStruct.Element1 == EElementsType::None)
		return;

	FElementsChanse* elementChanse = GetElementsData(damageStruct.Element1);
	float random = FMath::RandRange(0.0f, 100.0f);
	
	if (!elementChanse || random > damageStruct.ElementChanse)
		return;

	switch (damageStruct.Element1)
	{
	case EElementsType::Physical:
		ApplyPhysicalEffect(elementChanse);
		break;
	case EElementsType::Fire:
		ApplyFireEffect(damageStruct.Damage, elementChanse);
		break;
	case EElementsType::Lightning:
		ApplyLightningEffect(damageStruct.Damage, elementChanse);
		break;
	case EElementsType::Cold:
		ApplyColdEffect(elementChanse);
		break;
	case EElementsType::Poison:
		ApplyPoisonEffect(damageStruct.Damage, elementChanse);
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyPhysicalEffect(FElementsChanse* elementsChanseStruct)
{
	if (!elementsChanseStruct)
		return;

	++PhysicalEffect.CurrentStackPullEffect;
	if (PhysicalEffect.CurrentStackPullEffect < elementsChanseStruct->MaxStackPullEffect)
		return;

	PhysicalEffect.CurrentLifeTime = elementsChanseStruct->DeactivateEffectTime;
	PhysicalEffect.CurrentStackPullEffect = 0;

	if (PhysicalEffect.bIsEffect)
		return;


	ApplyElementalNiagara(PhysicalEffect, elementsChanseStruct);
	PhysicalEffect.bIsEffect = true;
	OnPhysicalEffect.ExecuteIfBound(true, elementsChanseStruct->ElementIcon);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::PhysicalTimerFunc()
{
	if (!PhysicalEffect.bIsEffect)
		return;

	PhysicalEffect.CurrentLifeTime -= BuffDebuffTimerTime;

	if (PhysicalEffect.CurrentLifeTime > 0.0)
		return;

	PhysicalEffect.bIsEffect = false;
	PhysicalEffect.NiagaraComponent = nullptr;

	OnPhysicalEffect.ExecuteIfBound(false, nullptr);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyFireEffect(float damage, FElementsChanse* elementsChanseStruct)
{
	if (!elementsChanseStruct)
		return;

	FFireEffectData fire = {};
	fire.CurrentLifeTime = 5;
	fire.Damage = damage;
	fire.FireData = *elementsChanseStruct;
	FireEffectArray.Add(fire);

	ApplyElementalNiagara(FireEffectArray[FireEffectArray.Num() - 1], elementsChanseStruct);

	OnFireEffect.ExecuteIfBound(true, FireEffectArray.Num() - 1, elementsChanseStruct->ElementIcon);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::FireTimerFunc()
{
	FDamageStruct damageStruct = {};
	damageStruct.DamageOwner = GetOwner();
	damageStruct.DamageOwnerComponent = this;

	for (int32 i = FireEffectArray.Num() - 1; i >= 0; --i)
	{
		FireEffectArray[i].CurrentLifeTime -= BuffDebuffTimerTime;

		if (!HasTimeEmplace(FireEffectArray[i], 1.0))
			continue;

		damageStruct.Damage = FMath::RandRange(FireEffectArray[i].FireData.ElementalPDMin, FireEffectArray[i].FireData.ElementalPDMax) / 100.0 * FireEffectArray[i].Damage;
		
		UE_LOG(LogTemp, Warning, TEXT("-[%S]- : Fire damage = %f"), __FUNCTION__, damageStruct.Damage);
		
		ApplyDamage(damageStruct);
		
		if (FireEffectArray[i].CurrentLifeTime <= 0)
		{
			OnFireEffect.ExecuteIfBound(false, i, nullptr);
			FireEffectArray.RemoveAt(i);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyColdEffect(FElementsChanse* elementsChanseStruct)
{
	if (!elementsChanseStruct)
		return;
	
	if (ColdEffect.CurrentStackPullEffect < elementsChanseStruct->MaxStackPullEffect)
	{
		++ColdEffect.CurrentStackPullEffect;
		ColdEffect.CurrentLifeTime = elementsChanseStruct->DeactivateEffectTime;
		GetOwner()->CustomTimeDilation = 1.0 - ColdEffect.CurrentStackPullEffect * elementsChanseStruct->StackEffect / 100;

		if(!ColdEffect.NiagaraComponent)
			ApplyElementalNiagara(ColdEffect, elementsChanseStruct);
		else
		{
			ColdEffect.NiagaraComponent->SetVariableFloat(FName(TEXT("LifeTime")), elementsChanseStruct->DeactivateEffectTime);
			ColdEffect.NiagaraComponent->ResetSystem();
		}

		OnColdEffect.ExecuteIfBound(true, ColdEffect.CurrentStackPullEffect, elementsChanseStruct->ElementIcon);
		ColdEffect.bIsEffect = true;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ColdTimerFunc()
{
	if (!ColdEffect.bIsEffect)
		return;

	ColdEffect.CurrentLifeTime -= BuffDebuffTimerTime;
	if (ColdEffect.CurrentLifeTime > 0.0)
		return;

	ColdEffect = {};
	GetOwner()->CustomTimeDilation = 1.0;
	OnColdEffect.ExecuteIfBound(false, 0, nullptr);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyPoisonEffect(float damage, FElementsChanse* elementsChanseStruct)
{
	if (!elementsChanseStruct)
		return;
	
	if (PoisonEffect.CurrentStackPullEffect >= elementsChanseStruct->MaxStackPullEffect)
		return;
	
	float randDamage = FMath::RandRange(elementsChanseStruct->ElementalPDMin, elementsChanseStruct->ElementalPDMax) / 100.0f * damage;
			
	ApplyElementalNiagara(PoisonEffect, elementsChanseStruct);

	PoisonEffect.Damage += randDamage;
	++PoisonEffect.CurrentStackPullEffect;
	OnPoisonEffect.ExecuteIfBound(true, PoisonEffect.CurrentStackPullEffect, elementsChanseStruct->ElementIcon);

	if (PoisonEffect.CurrentLifeTime <= 0.0)
	{
		PoisonEffect.bIsEffect = true;
		PoisonEffect.CurrentLifeTime = elementsChanseStruct->DeactivateEffectTime;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::PoisonTimerFunc()
{
	FDamageStruct damageStruct = {};
	damageStruct.DamageOwner = GetOwner();
	damageStruct.DamageOwnerComponent = this;

	if (!PoisonEffect.bIsEffect)
		return;

	damageStruct.Damage = PoisonEffect.Damage;
	PoisonEffect.CurrentLifeTime -= BuffDebuffTimerTime;

	if (!HasTimeEmplace(PoisonEffect, 2.0))
		return;

	UE_LOG(LogTemp, Warning, TEXT("-[%S]- : Poison damage = %f , Time = %f"), __FUNCTION__, PoisonEffect.Damage, PoisonEffect.CurrentLifeTime);
	ApplyDamage(damageStruct);

	if (PoisonEffect.CurrentLifeTime > 0.0)
		return;

	PoisonEffect = {};

	OnPoisonEffect.ExecuteIfBound(false, 0, nullptr);
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyLightningEffect(float damage, FElementsChanse* elementsChanseStruct)
{
	if (!elementsChanseStruct)
		return;
	FDamageStruct damageStruct = {};
	damageStruct.DamageOwner = GetOwner();
	damageStruct.DamageOwnerComponent = this;
	damageStruct.Damage = FMath::RandRange(elementsChanseStruct->ElementalPDMin, elementsChanseStruct->ElementalPDMax) / 100.0 * damage;
	
	UE_LOG(LogTemp, Warning, TEXT("-[%S]- : Lightnint damage = %f"), __FUNCTION__, damageStruct.Damage);
	ApplyDamage(damageStruct);

	ApplyElementalNiagara(LightningEffect, elementsChanseStruct);	
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplyElementalNiagara(FBuffDebuffMasterData& elementStruct, FElementsChanse* elementsChanseStruct)
{
	
	CHECK_PTR(elementsChanseStruct)	
	CHECK_CAST(CharacterOwner, ACharacterMaster, GetOwner())

	elementStruct.NiagaraComponent =	UNiagaraFunctionLibrary::SpawnSystemAttached(elementsChanseStruct->ElementNiagara, CharacterOwner->GetCharacterMesh(),
			FName(), FVector(0.0), FRotator(0.0), EAttachLocation::SnapToTarget, true);

	PTR(elementStruct.NiagaraComponent)->SetVariableFloat(FName(TEXT("LifeTime")), elementsChanseStruct->DeactivateEffectTime);

	if(!elementStruct.NiagaraComponent->OnSystemFinished.Contains(this, FName(TEXT("DestroyNiagaraAfter"))))
		elementStruct.NiagaraComponent->OnSystemFinished.AddDynamic(this, &UStateMasterComponent::DestroyNiagaraAfter);

}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::DestroyNiagaraAfter(UNiagaraComponent* pSystem)
{	
	if(pSystem)
		pSystem->DestroyComponent();
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::AuraEffect(USkillDefenseDA* SkillDA)
{
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::ApplySandStorm(USkillMasterDA* skillDA, float enemyDamage)
{
	USkillDefenseDA* defenseDA = Cast<USkillDefenseDA>(skillDA);
	FDamageStruct damageStruct = {};
	CHECK_PTR(defenseDA)
		
	damageStruct.DamageOwner = GetOwner();
	damageStruct.DamageOwnerComponent = this;

	SandDebuff.CurrentLifeTime = defenseDA->LifeTime;

	damageStruct.Damage = defenseDA->SkillPercent + enemyDamage;
	damageStruct.Element1 = defenseDA->SkillElement1;
	damageStruct.ElementChanse = FindElementChanseFromElement(defenseDA->SkillElement1);

	if (!SandDebuff.bIsEffect)
	{
		SandDebuff.bIsEffect = true;
		SandDebuffTimer(damageStruct);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStateMasterComponent::SandDebuffTimer(FDamageStruct& DamageStruct)
{
	FTimerHandle handle = {};

	if (SandDebuff.CurrentLifeTime <= 0.0)
	{
		SandDebuff.bIsEffect = false;
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(handle, [this, DamageStruct]()
		{
			FDamageStruct damageStruct = DamageStruct;

			ApplyDamage(damageStruct);
			SandDebuff.CurrentLifeTime -= 1.0;
			SandDebuffTimer(damageStruct);
		}, 1.0, false);
}
//-----------------------------------------------------------------------------------------------------------
bool UStateMasterComponent::HasTimeEmplace(FBuffDebuffMasterData& structData, float interval)
{
	structData.CurrentTickTime += BuffDebuffTimerTime;
	if (structData.CurrentTickTime < interval)
		return false;

	structData.CurrentTickTime -= interval;
	return true;
}