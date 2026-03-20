#pragma once

#include "ActorComponents/StorageComponent.h"
#include "ChestComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UChestComponent : public UStorageComponent
{
	GENERATED_BODY()

public:	
	UChestComponent();
	virtual void ApplyFastDrop(AFPSPlayerController* Controller, int32 Index, UInventorySlotWidget* WidgetSlot) override;
protected:
	virtual void BeginPlay() override;
		
};
//-----------------------------------------------------------------------------------------------------------