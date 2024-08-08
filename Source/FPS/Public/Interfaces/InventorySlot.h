#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventorySlot.generated.h"
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UInventorySlot : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IInventorySlot
{
	GENERATED_BODY()
public:
	virtual void UpdateInvSlot(TSoftObjectPtr<UTexture2D> Icon, int Count) = 0;
};
//-----------------------------------------------------------------------------------------------------------
