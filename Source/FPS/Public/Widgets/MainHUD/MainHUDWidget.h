#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorComponents/State/HealthStaminaComponent.h"
#include "MainHUDWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UProgressBarWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD Widget", meta = (BindWidget))
	UProgressBarWidget* WBPHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD Widget", meta = (BindWidget))
	UProgressBarWidget* WBPStamina;
protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void UpdateProgressBar(EStateName StateName, double CurrentValue, double MaxValue);
};
//-----------------------------------------------------------------------------------------------------------