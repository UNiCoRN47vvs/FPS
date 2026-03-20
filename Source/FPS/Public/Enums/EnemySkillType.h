#pragma once

#include "CoreMinimal.h"
#include "EnemySkillType.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EEnemySkillType : uint8
{
	None UMETA(DisplayName = "None"),
	Tier1 UMETA(DisplayName = "Tier1"),
	Tier2 UMETA(DisplayName = "Tier2"),
	Tier3 UMETA(DisplayName = "Tier3"),
	Tier4 UMETA(DisplayName = "Tier4"),
	Tier5 UMETA(DisplayName = "Tier5")
};
//-----------------------------------------------------------------------------------------------------------