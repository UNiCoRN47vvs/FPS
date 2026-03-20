#pragma once

#include "Config/SkillMasterDA.h"
#include "Enums/StateName.h"
#include "SkillDefenseDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USkillDefenseDA : public USkillMasterDA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Defence") double LifeTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Defence") double SkillPercent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Defence") EStateName SkillStateName;	
};
//-----------------------------------------------------------------------------------------------------------