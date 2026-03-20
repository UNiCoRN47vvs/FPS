#pragma once

#include "Widgets/Inventory/GenegalStorageWidget.h"
#include "Components/UniformGridPanel.h"
#include "StorageWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
class AFPSPlayerController;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStorageWidget : public UGenegalStorageWidget
{
	GENERATED_BODY()
public:
	virtual void UpdateSlots() override;
	virtual void InitStorageWidget(UStorageComponent* StorageComponent);

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UUniformGridPanel* UniformGridPanel;
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget") TSubclassOf<UUserWidget> SlotWidget;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() AFPSPlayerController* PlayerController;
private:

};
//-----------------------------------------------------------------------------------------------------------