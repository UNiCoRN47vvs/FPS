#pragma once

#include "Config/SkillMasterDA.h"
#include "SkillSupportDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class ASkillActor;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USkillSupportDA : public USkillMasterDA
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Support") TSoftClassPtr<ASkillActor> SkillActor;
};
//-----------------------------------------------------------------------------------------------------------