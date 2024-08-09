#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Interfaces/StorageInterface.h"
#include "InventoryWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventoryWidget : public UUserWidget, public IStorageInterface
{
	GENERATED_BODY()
public:
	UFUNCTION() void UpdateInventoryWidget();
	virtual UInventoryComponent* GetStorageComponent() override;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UUniformGridPanel* UniformGridPanel;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UButton* ButtonClose;
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget") TSubclassOf<UUserWidget> SlotWidget;
private:
	UFUNCTION() void InitInventoryWidget();
	UFUNCTION() void HideInventory();

	AFPSCharacter* PlayerCharacter;
};
//-----------------------------------------------------------------------------------------------------------
