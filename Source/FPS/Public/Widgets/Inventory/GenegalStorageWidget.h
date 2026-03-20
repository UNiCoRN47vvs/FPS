#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "GenegalStorageWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStorageComponent;
class UInventorySlotWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UGenegalStorageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void UpdateSlots();
	UPROPERTY() UStorageComponent* StorageComp;
};
//-----------------------------------------------------------------------------------------------------------