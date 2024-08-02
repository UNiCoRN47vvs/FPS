#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInteract.generated.h"
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UItemInteract : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IItemInteract
{
	GENERATED_BODY()

public:
	virtual FString GetItemInfo() = 0;
};
//-----------------------------------------------------------------------------------------------------------