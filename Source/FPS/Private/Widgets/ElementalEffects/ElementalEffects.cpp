#include "Widgets/ElementalEffects/ElementalEffects.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetComponent.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Widgets/ElementalEffects/ElementalEffectSlot.h"
//-----------------------------------------------------------------------------------------------------------
void UElementalEffects::NativeConstruct()
{
}
//-----------------------------------------------------------------------------------------------------------
void UElementalEffects::InitParams(UStateMasterComponent* stateMasterComponent)
{
	StateComponent = stateMasterComponent;
	CHECK_PTR(StateComponent)

	StateComponent->OnFireEffect.BindUObject(this, &UElementalEffects::TriggerFireIcon);
	StateComponent->OnPhysicalEffect.BindUObject(this, &UElementalEffects::TriggerPhysicalIcon);
	StateComponent->OnColdEffect.BindUObject(this, &UElementalEffects::TriggerColdIcon);
	StateComponent->OnPoisonEffect.BindUObject(this, &UElementalEffects::TriggerPoisonIcon);
}
//-----------------------------------------------------------------------------------------------------------
UElementalEffectSlot* UElementalEffects::CreateElementalSlot(const int32 stackEffect, UTexture2D* icon)
{
	UElementalEffectSlot* slot = CreateWidget<UElementalEffectSlot>(GetWorld(), WBPSlot);
	if (!slot || !ElementalSlotsSpaceHB)
	{
		ALARM_LOG
		return nullptr;
	}

	slot->UpdateSlot(0, icon);
	ElementalSlotsSpaceHB->AddChild(slot);
	return slot;
}
//-----------------------------------------------------------------------------------------------------------
void UElementalEffects::TriggerPhysicalIcon(const bool bIsCreate, UTexture2D* icon)
{
	if (!bIsCreate)
	{
		if (PhysicalSlot.IsValid())
			PhysicalSlot.Get()->RemoveFromParent();
		PhysicalSlot = nullptr;
		return;
	}

	PhysicalSlot = CreateElementalSlot(0, icon);
}
//-----------------------------------------------------------------------------------------------------------
void UElementalEffects::TriggerFireIcon(const bool bIsCreate, const int32 index, UTexture2D* icon)
{
	if (!bIsCreate)
	{
		if (FireArray.IsValidIndex(index) && FireArray[index].IsValid())
		{
			FireArray[index].Get()->RemoveFromParent();
			FireArray.RemoveAt(index);
		}
		return;
	}

	FireArray.Add(CreateElementalSlot(0, icon));
}
//-----------------------------------------------------------------------------------------------------------
void UElementalEffects::TriggerColdIcon(const bool bIsCreate, const int32 stackEffect, UTexture2D* icon)
{
	if (!bIsCreate)
	{
		if(ColdSlot.IsValid())
			ColdSlot.Get()->RemoveFromParent();
		ColdSlot = nullptr;
		return;
	}

	if (ColdSlot.IsValid())
	{
		ColdSlot->UpdateSlot(stackEffect, nullptr);
		return;
	}

	ColdSlot = CreateElementalSlot(stackEffect, icon);
}
//-----------------------------------------------------------------------------------------------------------
void UElementalEffects::TriggerPoisonIcon(const bool bIsCreate, const int32 stackEffect, UTexture2D* icon)
{
	if (!bIsCreate)
	{
		if (PoisonSlot.IsValid())
			PoisonSlot.Get()->RemoveFromParent();

		PoisonSlot = nullptr;
		return;
	}

	if (PoisonSlot.IsValid())
	{
		PoisonSlot.Get()->UpdateSlot(stackEffect, nullptr);
		return;
	}

	PoisonSlot = CreateElementalSlot(stackEffect, icon);
}
