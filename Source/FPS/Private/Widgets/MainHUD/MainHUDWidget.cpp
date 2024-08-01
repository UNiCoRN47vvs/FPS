#include "Widgets/MainHUD/MainHUDWidget.h"
#include "FPS/FPSCharacter.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AFPSCharacter* LocalPlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
	if (LocalPlayerCharacter)
	{
		UHealthStaminaComponent* LocalComponent = LocalPlayerCharacter->GetHealthStaminaComponent();
		if (LocalComponent)
			LocalComponent->OnChangeState.AddDynamic(this, &UMainHUDWidget::UpdateProgressBar);
		else
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("MainHUDWidget, LocalComponent = nullptr")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString(TEXT("MainHUDWidget, LocalPlayerCharacter = nullptr")));


}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::UpdateProgressBar(EStateName StateName, double CurrentValue, double MaxValue)
{
	switch (StateName)
	{
	case EStateName::Health:
	case EStateName::HealthMax:
		WBPHealth->SetValueProgressBar(CurrentValue, MaxValue);
		break;
	
	case EStateName::Stamina:
	case EStateName::StaminaMax:
		WBPStamina->SetValueProgressBar(CurrentValue, MaxValue);
		break;

	default:
		break;
	}
}
