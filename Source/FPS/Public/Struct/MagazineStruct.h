#pragma once

#include "CoreMinimal.h"
#include "MagazineStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UMagazineMasterDA;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FMagazine 
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Magazine Struct") UMagazineMasterDA* MagazineDA = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Magazine Struct") int32 CurrentAmmo = 0;
};
