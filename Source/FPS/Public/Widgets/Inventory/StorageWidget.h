#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Interfaces/StorageInterface.h"
#include "StorageWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStorageWidget : public UUserWidget, public IStorageInterface
{
	GENERATED_BODY()
public:
	virtual UStorageComponent* GetStorageComponent() override;
	UFUNCTION() void UpdateInventoryWidget();

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UUniformGridPanel* UniformGridPanel;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UButton* ButtonClose;
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget") TSubclassOf<UUserWidget> SlotWidget;
	UFUNCTION() void InitStorageWidget(UStorageComponent* StorageComponent);
	AFPSCharacter* PlayerCharacter;
private:

};
//-----------------------------------------------------------------------------------------------------------