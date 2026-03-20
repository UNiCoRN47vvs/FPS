#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Enums/StateName.h"
#include "EnemyStateWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStateMasterComponent;
class UElementalEffects;
class UProgressBarWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemyStateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitParams(UStateMasterComponent* stateMasterComponent);

	UPROPERTY(BlueprintReadOnly, Category = "E_S_W", meta = (BindWidget)) UElementalEffects* ElementalEffects;
	UPROPERTY(BlueprintReadOnly, Category = "E_S_W", meta = (BindWidget)) UProgressBarWidget* HealthBar;
protected:
	UFUNCTION() void UpdateHealth(EStateName stateName, float currentHealth, float maxHealth);
	UPROPERTY() UStateMasterComponent* StateComponent;
};
//-----------------------------------------------------------------------------------------------------------