#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInteract.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
struct FItemStructMaster;
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
	virtual FItemStructMaster GetItemInfo() = 0;
	virtual void InteractWithActor(AFPSCharacter* PlayerCharacter) = 0;
};
//-----------------------------------------------------------------------------------------------------------