#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DragDropInterface.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInventoryComponent;
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UDragDropInterface : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IDragDropInterface
{
	GENERATED_BODY()
public:
	virtual void DragDropOperation(UInventoryComponent* StorageComponent, int Index, bool bIsDrop) = 0;
};
//-----------------------------------------------------------------------------------------------------------