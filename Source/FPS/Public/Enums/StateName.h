#pragma once

#include "CoreMinimal.h"
#include "StateName.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
	enum class EStateName : uint8
{
	Health						UMETA(DisplayName = "Health"),
	HealthMax					UMETA(DisplayName = "Health Max"),
	HealthRegen					UMETA(DisplayName = "Health Regen"),
	Stamina						UMETA(DisplayName = "Stamina"),
	StaminaMax					UMETA(DisplayName = "Stamina Max"),
	StaminaRegen				UMETA(DisplayName = "Stamina Regen"),
	Mana							UMETA(DisplayName = "Mana"),
	ManaMax						UMETA(DisplayName = "Mana Max"),
	ManaRegen					UMETA(DisplayName = "Mana Regen"),
	Weight						UMETA(DisplayName = "Weight"),
	PhysicalResistance		UMETA(DisplayName = "Physical Resistance"),
	FireResistance				UMETA(DisplayName = "Fire Resistance"),
	ColdResistance				UMETA(DisplayName = "Cold Resistance"),
	PoisonResistance			UMETA(DisplayName = "Poison Resistance"),
	LightningResistance		UMETA(DisplayName = "Lightning Resistance"),
	PhysicalElementChance	UMETA(DisplayName = "Physical Element Chance"),
	FireElementChance			UMETA(DisplayName = "Fire Element Chance"),
	ColdElementChance			UMETA(DisplayName = "Cold Element Chance"),
	PoisonElementChance		UMETA(DisplayName = "Poison Element Chance"),
	LightningElementChance	UMETA(DisplayName = "Lightning Element Chance"),
	Vampiric1					UMETA(DisplayName = "Vampiric Level 1"),
	Vampiric2					UMETA(DisplayName = "Vampiric Level 2"),
	Vampiric3					UMETA(DisplayName = "Vampiric Level 3"),
	DescreaceSkillCooldown	UMETA(DisplayName = "Descreace Skill Cooldown"),
	ScrollSaveChance			UMETA(DisplayName = "Scroll Save Chance"),

};

//for (EMyEnum Value : TEnumRange<EMyEnum>())
//ENUM_RANGE_BY_FIRST_AND_LAST(EStateName, EStateName::Health, EStateName::LightningElementChance)

