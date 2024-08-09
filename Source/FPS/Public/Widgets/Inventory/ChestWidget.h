#pragma once

#include "Widgets/Inventory/StorageWidget.h"
#include "ChestWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UChestWidget : public UStorageWidget
{
	GENERATED_BODY()
public:
	virtual UStorageComponent* GetStorageComponent() override;
protected:
	virtual void NativeConstruct() override;
};
//-----------------------------------------------------------------------------------------------------------