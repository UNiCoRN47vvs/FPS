#pragma once

#include "ActorComponents/Skill/SkillMasterComponent.h"
#include "EnemySC.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UNiagaraComponent;
class UAIBrainComponent;
class UEnemyStateComponent;
class ACharacterMaster;
class AEnemyMaster;
class UEnemyMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemySC : public USkillMasterComponent
{
	GENERATED_BODY()

public:
	void InitEnemySC(AEnemyMaster* enemyOwner, UEnemyMasterDA* enemyDA, APawn* pawnTarget);
	void SetEnemyDamage(const FStatRange& enemyDamage);

	template <typename DataAssetClass>	DataAssetClass* GetCurrentSkillDA()
	{
		return Cast<DataAssetClass>(CurrentSkill.SkillData);
	};


#pragma region Skills
	void UseDefenseSkill();
	void UseSkillStrike();
	void UseSkillMultiStrike();
	void UseSkillTripleProjectile();
	void UseSkillMelee();
	void UseSkillHomingProjectile();
	void UseSkillIcecleProjectile();
	void UseSkillProjectileSpawner();
	void UseSkillIceCage();
	void UseSkillBubble();
	void UseSkillAura();
	void UseSkillLifeSteal();
	void UseTeleportToPlayer();
	void UseSkillLifeChainAttack();
	void UseSkillSircleWave();
	void UseSkillDilationUpBuff();
	void UseSkillSandStorm();
	void UseSkillFrostveilMelee();
	void UseSkillFrostveilHand();
	void UseSkillFrostveilAura();
	void UseSkillBlizzard();
#pragma endregion

#pragma region Passive
	void FrostveilPassive();
#pragma endregion

	UFUNCTION() void AttackEnded();

	FEnemySkillsData CurrentSkill;
protected:
	UFUNCTION() void UseSkillStrikeStep2(UNiagaraComponent* FinishedComponent);
	void SkillLifeStealNiagaraEffect(UNiagaraComponent* niagara, FVector location);
	void DealDamageIfNotSpawn(FDamageStruct& damageStruct);
	void SpawnSkillProjectile(bool bIsHoming);
	void FrostveilAuraSubFunc(UWorld* world, float auraLifeTime, const float auraRadius, const FDamageStruct auraDamage, FStatRange enemyDamage);

	ACharacterMaster* TryGetPlayerCharacter(float radius, const FVector& location, UWorld* world = nullptr);
	UAIBrainComponent* GetAIBrainComponent();
	UStateMasterComponent* GetEnemyStateComponent();

	UPROPERTY() APawn* PawnTarget;
	UPROPERTY() AEnemyMaster* EnemyOwner;
	UPROPERTY() UEnemyMasterDA* EnemyDA;
	UPROPERTY() UAIBrainComponent* AIBrainComponent;
	UPROPERTY() UEnemyStateComponent* EnemyStateComponent;

	FVector StrikeLocation;
	FStatRange EnemyDamage;
	FDamageStruct DamageStruct;

private:
	bool CheckData();
};
//-----------------------------------------------------------------------------------------------------------