#pragma once

#include "SkillActors/SkillActor.h"
#include "SpecializedSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ASpecializedSA : public ASkillActor
{
	GENERATED_BODY()
public:
	void InitParam(float damage, UEnemyMasterDA* enemyMasterDA, AEnemyMaster* enemy, USkillAttackDA* skillDA = nullptr) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "S_A_M") float EnemyDamage;
	UPROPERTY(BlueprintReadOnly, Category = "S_A_M") UEnemyMasterDA* EnemyDA;
	UPROPERTY(BlueprintReadOnly, Category = "S_A_M") AEnemyMaster* EnemyCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "S_A_M") USkillAttackDA* SKillAttackDA;
};
//-----------------------------------------------------------------------------------------------------------