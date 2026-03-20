#include "Widgets/Enemy/EnemyStateWidget.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Widgets/ElementalEffects/ElementalEffects.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateWidget::InitParams(UStateMasterComponent* stateMasterComponent)
{
	CHECK_PTR(stateMasterComponent)

	StateComponent = stateMasterComponent;
	StateComponent->OnChangeState.AddUObject(this, &UEnemyStateWidget::UpdateHealth);

	ElementalEffects->InitParams(StateComponent);
	HealthBar->ValueTextBlock->SetVisibility(ESlateVisibility::Collapsed);
}
//-----------------------------------------------------------------------------------------------------------
void UEnemyStateWidget::UpdateHealth(EStateName stateName, float currentHealth, float maxHealth)
{
	switch (stateName)
	{
	case EStateName::HealthMax:
	case EStateName::HealthRegen:
	case EStateName::Stamina:
	case EStateName::StaminaMax:
	case EStateName::StaminaRegen:
	case EStateName::Weight:
	case EStateName::PhysicalResistance:
	case EStateName::FireResistance:
	case EStateName::ColdResistance:
	case EStateName::PoisonResistance:
	case EStateName::LightningResistance:
		return;
		break;
	default:
		break;
	}

	HealthBar->SetVisibility(ESlateVisibility::Visible);
	HealthBar->SetValueProgressBar(currentHealth, maxHealth);
}
