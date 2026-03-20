#pragma once

#include "CoreMinimal.h"
#include "Enums/EnemySkillType.h"
#include "Config/SkillAttackDA.h"
#include "Config/SkillDefenseDA.h"
#include "Config/SkillSupportDA.h"
#include "EnemySkillsData.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FEnemySkillsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Skills Data") EEnemySkillType SkillType = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Skills Data") USkillMasterDA* SkillData = nullptr;
	
};
