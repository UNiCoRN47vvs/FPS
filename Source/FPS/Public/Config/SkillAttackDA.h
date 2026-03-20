#pragma once

#include "Config/SkillMasterDA.h"
#include "Struct/StatRange.h"
#include "SkillAttackDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AProjectileActorMaster;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USkillAttackDA : public USkillMasterDA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_D") FStatRange SkillAttackDamage = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_D") TSubclassOf<AActor> AttackProjectyle = nullptr;
};
//-----------------------------------------------------------------------------------------------------------