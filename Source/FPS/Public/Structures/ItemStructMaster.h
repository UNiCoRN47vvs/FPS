#pragma once

#include "CoreMinimal.h"
#include "ItemStructMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FPS_API FItemStructMaster
{
	GENERATED_BODY()

	FName ItemName;
	FText ItemDesc;
	TSoftObjectPtr<UTexture2D> ItemIcon;
	TSoftObjectPtr<UStaticMesh> ItemStaticMesh;

};
//-----------------------------------------------------------------------------------------------------------