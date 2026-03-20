#pragma once

#include "SkillActors/ProjectileSA.h"
#include "ProjectileSpawnerSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AProjectileSpawnerSA : public AProjectileSA
{
	GENERATED_BODY()
public:
	virtual void InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA) override;

protected:
	void SpawnProjectile();

	UPROPERTY() USkillAttackDA* SkillProjectileDA;
};
//-----------------------------------------------------------------------------------------------------------