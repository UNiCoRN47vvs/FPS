#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInteract.generated.h"
//-----------------------------------------------------------------------------------------------------------
class ACharacterMaster;
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
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) = 0;
};
//-----------------------------------------------------------------------------------------------------------