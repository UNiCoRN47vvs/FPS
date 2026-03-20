#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EItemType : uint8
{
	All UMETA(DisplayName = "All"),
	Currency UMETA(DisplayName = "Currency"),
	Supplies UMETA(DisplayName = "Supplies"),
	PortalStone UMETA(DisplayName = "Portal Stone"),
	PortalDungeon UMETA(DisplayName = "Portal Dungeon"),
	ConsumableSupplies UMETA(DisplayName = "Consumable Supplies"),
	Potion UMETA(DisplayName = "Potion"),
	QuestItem UMETA(DisplayName = "Quest Item"),
	Armor UMETA(DisplayName = "Armor"),
	Magazine UMETA(DisplayName = "Magazine"),
	MagicWeapon UMETA(DisplayName = "Magic Weapon"),
	MagicMagazine UMETA(DisplayName = "Magic Magazine"),
	Audus UMETA(DisplayName = "Audus"),
	ScrollSkill UMETA(DisplayName = "Scroll Skill"),
	StoreSlot UMETA(DisplayName = "Store Slot"),
	Rune UMETA(DisplayName = "Rune"),
	MAX UMETA(Hidden)
};
