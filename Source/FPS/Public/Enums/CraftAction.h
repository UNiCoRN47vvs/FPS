#pragma once

#include "CoreMinimal.h"
#include "CraftAction.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class ECraftAction : uint8
{
	Add			UMETA(DisplayName = "Add"),
	Remove		UMETA(DisplayName = "Remove"),
	Giver			UMETA(DisplayName = "Giver"),
	RandomGiver UMETA(DisplayName = "Random Giver"),
	AddStat		UMETA(DisplayName = "Add Stat"),
	RemoveStat	UMETA(DisplayName = "Remove Stat"),
	
};
//-----------------------------------------------------------------------------------------------------------
