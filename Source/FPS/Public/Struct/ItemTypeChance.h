#pragma once

#include "CoreMinimal.h"
#include "ItemTypeChance.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class ETypeChance : uint8
{
	SecondChance	UMETA(DisplayName = "Second Chance"),
	Currency			UMETA(DisplayName = "Currency"),
	Supplies			UMETA(DisplayName = "Supplies"),
	PortalDungeon	UMETA(DisplayName = "Portal Dungeon"),
	PortalStone		UMETA(DisplayName = "Portal Stone"),
	SkillScroll		UMETA(DisplayName = "Skill Scroll"),
	Audus				UMETA(DisplayName = "Audus"),
	Armor				UMETA(DisplayName = "Armor"),
	Magazine			UMETA(DisplayName = "Magazine"),
	MagicWeapon		UMETA(DisplayName = "Magic Weapon"),
	Rune				UMETA(DisplayName = "Rune"),
	Fail				UMETA(DisplayName = "Fail")

};
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemTypeChance: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") ETypeChance ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") float Chance;
};
