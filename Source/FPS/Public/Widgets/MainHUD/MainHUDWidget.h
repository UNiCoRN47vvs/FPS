#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorComponents/State/HealthStaminaComponent.h"
#include "MainHUDWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UProgressBarWidget;
class UInventoryWidget;
class UInventoryComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void DragDropOperation(UInventoryComponent* StorageComponent, int Index, bool bIsDrop);
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD Widget", meta = (BindWidget)) UProgressBarWidget* WBPHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD Widget", meta = (BindWidget)) UProgressBarWidget* WBPStamina;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD Widget", meta = (BindWidget)) UInventoryWidget* WBPInventory;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()	void UpdateProgressBar(EStateName StateName, double CurrentValue, double MaxValue);
private:
	UInventoryComponent* DragStorage;
	UInventoryComponent* DropStorage;
	int DragIndex;
	int DropIndex;
};
//-----------------------------------------------------------------------------------------------------------