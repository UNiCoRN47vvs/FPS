#pragma once

#include "CoreMinimal.h"
#include "SortType.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class ESortType : uint8
{
	SortType UMETA(DisplayName = "Type"),
	SortGrade UMETA(DisplayName = "Grade"),
	SortName UMETA(DisplayName = "Name")
};

//-----------------------------------------------------------------------------------------------------------