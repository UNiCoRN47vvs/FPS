#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInfo.generated.h"
//-----------------------------------------------------------------------------------------------------------
struct FInteractStruct;
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UInteractInfo : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IInteractInfo
{
	GENERATED_BODY()

public:
	virtual FInteractStruct GetInteractInfo() = 0;
};
//-----------------------------------------------------------------------------------------------------------