#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION() void UpdateInventoryWidget();
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UUniformGridPanel* UniformGridPanel;
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget") TSubclassOf<UUserWidget> SlotWidget;
private:
	UFUNCTION() void InitInventoryWidget();

	AFPSCharacter* PlayerCharacter;
};
//-----------------------------------------------------------------------------------------------------------
