#pragma once

#include "ActorComponents/StorageComponent.h"
#include "InventoryComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInventoryComponent : public UStorageComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	bool PickUpItem(FItemInvStruct& ItemStruct);
	
protected:
	virtual void BeginPlay() override;
};
//-----------------------------------------------------------------------------------------------------------
