#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInfo.generated.h"
//-----------------------------------------------------------------------------------------------------------
struct FItemStructMaster;
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UItemInfo : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IItemInfo
{
	GENERATED_BODY()

public:
	virtual FItemStructMaster GetItemInfo() = 0;
};
//-----------------------------------------------------------------------------------------------------------