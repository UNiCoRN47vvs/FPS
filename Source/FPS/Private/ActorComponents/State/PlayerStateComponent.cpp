#include "ActorComponents/State/PlayerStateComponent.h"
#include "TimerManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "Config/SkillDefenseDA.h"
#include "Struct/DamageStruct.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
TDelegate<void(APawn*, USkillDefenseDA*)> UPlayerStateComponent::OnApplyIceCage;
//-----------------------------------------------------------------------------------------------------------
UPlayerStateComponent::UPlayerStateComponent()
{
	
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::BeginPlay()
{
	Super::BeginPlay();
	StandartStateMap = StateMap;
	PlayerCharacter = GetOwner<AFPSCharacter>();
	if (PlayerCharacter && PlayerCharacter->GetEquipmentComponent())
	{
		PlayerCharacter->OnChangeSprint.AddUObject(this, &UPlayerStateComponent::WasteStaminaTimerManager);
		PlayerCharacter->GetEquipmentComponent()->OnChangeEquipStat.BindUObject(this, &UPlayerStateComponent::SetEquipStat);
	}

	OnChangeState.AddUObject(this, &UPlayerStateComponent::RegenTimerManager);
	OnChangeState.Broadcast(EStateName::Health, GetStateMapElem(EStateName::Health), GetStateMapElem(EStateName::HealthMax));
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));
	OnChangeState.Broadcast(EStateName::Mana, GetStateMapElem(EStateName::Mana), GetStateMapElem(EStateName::ManaMax));

	UEventBus::OnUseConsumableSupplies.BindUObject(this, &UPlayerStateComponent::UseConsumableSupplies);
	UEventBus::OnWeightCalculation.BindUObject(this, &UPlayerStateComponent::WeightCalculation);
	UEventBus::OnPlayerElementsChance.BindUObject(this, &UPlayerStateComponent::FindElementChanseFromElement);
	UEventBus::OnGetPlayerStateMap.BindUObject(this, &UPlayerStateComponent::GetStateMap);

	OnApplyIceCage.BindUObject(this, &UPlayerStateComponent::ApplyIceCage);
}
void UPlayerStateComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UEventBus::OnUseConsumableSupplies.Unbind();
	UEventBus::OnWeightCalculation.Unbind();
	UEventBus::OnPlayerElementsChance.Unbind();
	UEventBus::OnGetPlayerStateMap.Unbind();

	OnApplyIceCage.Unbind();

	if (PlayerCharacter && PlayerCharacter->GetEquipmentComponent())
	{
		PlayerCharacter->OnChangeSprint.RemoveAll(this);
		PlayerCharacter->GetEquipmentComponent()->OnChangeEquipStat.Unbind();
	}
}
//-----------------------------------------------------------------------------------------------------------
// Логика управления таймерами регенерации здоровья, выносливости и маны
void UPlayerStateComponent::RegenTimerManager(EStateName stateName, float currentValue, float maxValue)
{
	float timerTime = 0.0f;
	FTimerHandle* timerHandle = nullptr;
	FTimerDelegate timerDel = {};
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	switch (stateName) // Определяем, какой таймер нужен для регенерации состояния
	{
	case EStateName::Health:
	{
		timerHandle = &HealthTimerHandle;
		timerDel.BindLambda([this]() 
			{ 
				ChangeStateValue(EStateName::Health, GetStateMapElem(EStateName::HealthRegen), true); 
			});

		timerTime = 10.0f;
		break;
	}
	
	case EStateName::Stamina:
	{
		timerHandle = &StaminaTimerHandle;
		timerDel.BindLambda([this]()
			{ 
				if(!bStaminaTimerBlock)
					ChangeStateValue(EStateName::Stamina, GetStateMapElem(EStateName::StaminaRegen), true);  
			});

		timerTime = 1.0f;
		break;
	}
	case EStateName::Mana:
	{
		timerHandle = &ManaTimerHandle;
		timerDel.BindLambda([this]() 
			{
				ChangeStateValue(EStateName::Mana, GetStateMapElem(EStateName::ManaRegen), true);
			});
		timerTime = 5.0f;
		break;
	}
	
	default:
		break;
	}
	CHECK_PTR(timerHandle)

	if (currentValue >= maxValue)
	{
		timerManager.ClearTimer(*timerHandle);
		return;
	}

	if(!timerManager.TimerExists(*timerHandle))
		timerManager.SetTimer(*timerHandle, timerDel, timerTime, true);
}
//-----------------------------------------------------------------------------------------------------------
// Логика управления таймером расхода выносливости
void UPlayerStateComponent::WasteStaminaTimerManager(bool bStart)
{
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	if (bStart && !timerManager.TimerExists(WasteStaminaTimerHandle))
	{
		timerManager.SetTimer(WasteStaminaTimerHandle, this, &UPlayerStateComponent::WasteStamina, 0.2,  true);
		bStaminaTimerBlock = true;
		bIsSprinting = true;
	}
	else if (!bStart && timerManager.TimerExists(WasteStaminaTimerHandle))
	{
		timerManager.ClearTimer(WasteStaminaTimerHandle);
		bStaminaTimerBlock = false;
		bIsSprinting = false;
	}
}
void UPlayerStateComponent::WasteStamina()
{
	float* stamina = StateMap.Find(EStateName::Stamina);
	CHECK_PTR(stamina)

	*stamina -= 1;
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));

	if (GetStateMapElem(EStateName::Stamina) <= 0.5)
	{
		PTR(PlayerCharacter)->Sprint<false>();
		WasteStaminaTimerManager(false);
	}
}
//-----------------------------------------------------------------------------------------------------------
bool UPlayerStateComponent::WasteMana(float manaCost, bool bIsWasteMana)
{
	if(!StateMap.Contains(EStateName::Mana) || *StateMap.Find(EStateName::Mana) < manaCost)
		return false;

	if (!bIsWasteMana)
		return true;

	*StateMap.Find(EStateName::Mana) -= manaCost;
	OnChangeState.Broadcast(EStateName::Mana, GetStateMapElem(EStateName::Mana), GetStateMapElem(EStateName::ManaMax));
	return true;
}
//-----------------------------------------------------------------------------------------------------------
// Логика изменения значений состояний (здоровье, выносливость)
void UPlayerStateComponent::ChangeStateValue(EStateName stateName, float value, bool bIncreaseState)
{
	float* currentValue = StateMap.Contains(stateName) ? StateMap.Find(stateName) : nullptr;
	float* maxValue = nullptr;

	switch (stateName) // Определяем максимальное значение для здоровья или выносливости
	{
	case EStateName::Health:
		if(StateMap.Contains(EStateName::HealthMax))
			maxValue = StateMap.Find(EStateName::HealthMax);
		break;

	case EStateName::Stamina:
		if (StateMap.Contains(EStateName::StaminaMax))
			maxValue = StateMap.Find(EStateName::StaminaMax); 
		break;
	case EStateName::Mana:
		if (StateMap.Contains(EStateName::ManaMax))
			maxValue = StateMap.Find(EStateName::ManaMax); 
		break;

	default:
		break;
	}

	if (currentValue && maxValue)
	{
		if (bIncreaseState)
			*currentValue = FMath::Clamp(*currentValue + value, 0.0, *maxValue);
		else
			*currentValue = FMath::Clamp(*currentValue - value, 0.0, *maxValue);

		OnChangeState.Broadcast(stateName, *currentValue, *maxValue);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::UseConsumableSupplies(const TMap<EStateName, float>& stats)
{
	float* param = nullptr;
	for (auto& stat : stats)
	{
		switch (stat.Key)
		{
		case EStateName::Health:
		case EStateName::Stamina:
		case EStateName::Mana:
		{
			param = StateMap.Find(stat.Key);
			if (!param)
			{
				ALARM_LOG
				continue;
			}
			*param += stat.Value;
			if (GetStateMapElem(EStateName::Health) > GetStateMapElem(EStateName::HealthMax))
				*StateMap.Find(EStateName::Health) = GetStateMapElem(EStateName::HealthMax);
			if (GetStateMapElem(EStateName::Stamina) > GetStateMapElem(EStateName::StaminaMax))
				*StateMap.Find(EStateName::Stamina) = GetStateMapElem(EStateName::StaminaMax);
			if (GetStateMapElem(EStateName::Mana) > GetStateMapElem(EStateName::ManaMax))
				*StateMap.Find(EStateName::Mana) = GetStateMapElem(EStateName::ManaMax);

			break;
		}
		case EStateName::HealthRegen:
		case EStateName::StaminaRegen:
		case EStateName::Weight:
		case EStateName::HealthMax:
		case EStateName::StaminaMax:
		{

			break;
		}
		default:
			break;

		}
	}

	OnChangeState.Broadcast(EStateName::Health, GetStateMapElem(EStateName::Health), GetStateMapElem(EStateName::HealthMax));
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));
	OnChangeState.Broadcast(EStateName::Mana, GetStateMapElem(EStateName::Mana), GetStateMapElem(EStateName::ManaMax));
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::WeightCalculation()
{
	if (!InventoryComponent)
	{
		InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();
		CHECK_PTR(InventoryComponent)
	}
	
	float weight = 0.0f;
	const TArray<FItemInvStruct>& storage = InventoryComponent->GetStorage();

	for (const FItemInvStruct& item : storage)
	{
		if (!item.bOccupied)
			continue;
		//Разделение для работы аларма на нульпоинтер а не на пустую ячейку
		if (!item.ItemDA)
		{
			ALARM_LOG
			continue;
		}

		for(int32 i = 0; i < item.ItemCount; ++i)
			weight += item.ItemDA->ItemWeight;
	}

	*StateMap.Find(EStateName::Weight) = weight;
	UEventBus::OnUpdateWeight.ExecuteIfBound(weight);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::ApplyIceCage(APawn* target, USkillDefenseDA* skillDA)
{
	if (target != PlayerCharacter || !skillDA)
		return;

	IceCageStruct.Time = skillDA->LifeTime;

	if (IsValid(IceCageStruct.NiagaraComponent))
		IceCageStruct.NiagaraComponent->DestroyComponent();
	
	IceCageStruct.NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, skillDA->SkillEffect[0], FVector{}, FRotator{}, FVector{ 1.0 }, false);

	CHECK_PTR(IceCageStruct.NiagaraComponent)
	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	IceCageStruct.NiagaraComponent->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	IceCageStruct.NiagaraComponent->SetAbsolute(false, true, false);
	IceCageStruct.NiagaraComponent->SetFloatParameter(FName(TEXT("LifeTime")), IceCageStruct.Time);
	IceCageStruct.NiagaraComponent->ResetSystem();

	if (IceCageStruct.bIsExist)
		return;

	IceCageStruct.bIsExist = true;
	IceCageStruct.SpeedPercent = skillDA->SkillPercent;
	PlayerCharacter->SpeedPercent -= skillDA->SkillPercent;

	GetWorld()->GetTimerManager().SetTimer(IceCageTimerHandle, this, &UPlayerStateComponent::RemoveIceCage, 0.1f, true);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::RemoveIceCage()
{
	IceCageStruct.Time -= 0.1f;
	if (IceCageStruct.Time > 0.0f)
		return;

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	PlayerCharacter->SpeedPercent += IceCageStruct.SpeedPercent;
	
	IceCageStruct = {};
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::SetEquipStat(const FStatValueStruct& armorStat)
{
	if (!StateMap.Contains(EStateName::Health) 
		|| !StateMap.Contains(EStateName::Stamina) 
		|| !StateMap.Contains(EStateName::Mana))
		return;

	float health = *StateMap.Find(EStateName::Health);
	float stamina = *StateMap.Find(EStateName::Stamina);
	float mana = *StateMap.Find(EStateName::Mana);

	StateMap = StandartStateMap;

	for (const auto& item : armorStat.StatsValue)
	{
		if (StateMap.Contains(item.Key))
			*StateMap.Find(item.Key) += item.Value;
		else
			StateMap.Add(item.Key, item.Value);
	}

	if (health > *StateMap.Find(EStateName::HealthMax))
		health = *StateMap.Find(EStateName::HealthMax);

	if (stamina > *StateMap.Find(EStateName::StaminaMax))
		stamina = *StateMap.Find(EStateName::StaminaMax);

	if (mana > *StateMap.Find(EStateName::ManaMax))
		mana = *StateMap.Find(EStateName::ManaMax);

	*StateMap.Find(EStateName::Health)		  = health;
	*StateMap.Find(EStateName::Stamina)		  = stamina;
	*StateMap.Find(EStateName::Mana)			  = mana;

	OnChangeState.Broadcast(EStateName::Health, GetStateMapElem(EStateName::Health), GetStateMapElem(EStateName::HealthMax));
	OnChangeState.Broadcast(EStateName::Stamina, GetStateMapElem(EStateName::Stamina), GetStateMapElem(EStateName::StaminaMax));
	OnChangeState.Broadcast(EStateName::Mana, GetStateMapElem(EStateName::Mana), GetStateMapElem(EStateName::ManaMax));

	InitSpecificStat();
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerStateComponent::AuraEffect(USkillDefenseDA* SkillDA)
{
	Super::AuraEffect(SkillDA);
	CHECK_PTR(SkillDA)

	FDamageStruct damageStruct = {};
	damageStruct.DamageOwner = GetOwner();
	damageStruct.DamageOwnerComponent = this;
	damageStruct.Damage	= SkillDA->SkillPercent;
	damageStruct.Element1 = SkillDA->SkillElement1;
	ApplyDamage(damageStruct);
}

