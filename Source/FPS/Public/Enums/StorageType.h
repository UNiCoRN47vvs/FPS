#pragma once

#include "CoreMinimal.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EStorageType : uint8
{
	Chest,
	TreasureInventory,
	Upgrade,
	Portal,
	Inventory,
	Equipment,
	Store,
	Quests,
	Craft
};
//-----------------------------------------------------------------------------------------------------------