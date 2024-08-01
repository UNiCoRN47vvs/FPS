#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInteract.generated.h"
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UPlayerInteract : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IPlayerInteract
{
	GENERATED_BODY()


public:

	virtual void InteractPlayerWithItem(bool bTurnOn) = 0;
};
//-----------------------------------------------------------------------------------------------------------