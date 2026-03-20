#pragma once

#include "Config/SkillAttackDA.h"
#include "SkillProjectileSpawnerDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USkillProjectileSpawnerDA : public USkillAttackDA
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") float SpawnRateProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") USkillAttackDA* SpawnProjectileDA;
};
//-----------------------------------------------------------------------------------------------------------