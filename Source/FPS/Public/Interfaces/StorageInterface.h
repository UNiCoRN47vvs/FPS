#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StorageInterface.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStorageComponent;
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UStorageInterface : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IStorageInterface
{
	GENERATED_BODY()

public:
	virtual UStorageComponent* GetStorageComponent() = 0;
};
//-----------------------------------------------------------------------------------------------------------