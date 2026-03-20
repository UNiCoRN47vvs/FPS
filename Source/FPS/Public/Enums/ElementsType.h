#pragma once

#include "CoreMinimal.h"
#include "ElementsType.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EElementsType : uint8
{
	None UMETA(DisplayName = "None"),
	Physical UMETA(DisplayName = "Physical"),
	Fire UMETA(DisplayName = "Fire"),
	Lightning UMETA(DisplayName = "Lightning"),
	Cold UMETA(DisplayName = "Cold"),
	Poison UMETA(DisplayName = "Poison")

};
