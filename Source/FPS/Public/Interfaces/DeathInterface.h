#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DeathInterface.generated.h"
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UDeathInterface : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IDeathInterface
{
	GENERATED_BODY()

public:
	virtual void ApplyDeath() = 0;
};
//-----------------------------------------------------------------------------------------------------------