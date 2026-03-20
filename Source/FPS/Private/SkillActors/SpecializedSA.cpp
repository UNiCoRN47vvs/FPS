#include "SkillActors/SpecializedSA.h"
#include "Enemies/EnemyMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
//-----------------------------------------------------------------------------------------------------------
void ASpecializedSA::InitParam(float damage, UEnemyMasterDA* enemyMasterDA, AEnemyMaster* enemy, USkillAttackDA* skillDA)
{
	if (!enemy)
	{
		ALARM_LOG
			Destroy();

		return;
	}

	EnemyDamage = damage;
	EnemyDA = enemyMasterDA;
	EnemyCharacter = enemy;
	SKillAttackDA = skillDA;
	ActivateSkill();

	DamageStruct.DamageOwner = enemy;
	DamageStruct.DamageOwnerComponent = enemy->FindComponentByClass<UStateMasterComponent>();
}
//-----------------------------------------------------------------------------------------------------------
