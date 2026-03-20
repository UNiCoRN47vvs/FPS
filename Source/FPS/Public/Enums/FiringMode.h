#pragma once

#include "CoreMinimal.h"
#include "FiringMode.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EFiringMode : uint8
{
	Auto UMETA(DisplayName = "Auto"),
	ShotGun UMETA(DisplayName = "ShotGun"),
	Snipe UMETA(DisplayName = "Snipe"),
};
