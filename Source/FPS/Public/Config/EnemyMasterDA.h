#pragma once

#include "CoreMinimal.h"
#include "Config/CharacterMasterDA.h"
#include "Struct/EnemySkillsData.h"
#include "Struct/StatRange.h"
#include "Enums/StateName.h"
#include "EnemyMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AEnemyMaster;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemyMasterDA : public UCharacterMasterDA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") float AttackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") float AttackSphereRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") FStatRange EnemyAttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") FName InteractButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") FName IteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") FName EnemyName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") UNiagaraSystem* TakingHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") FLinearColor TakingHitEffectColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") TArray<FEnemySkillsData> EnemySkills;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") TMap<EStateName, float> EnemyStateMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Master") TSoftObjectPtr<UNiagaraSystem> IllusionDeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot") UDataTable* DTSpecialDrop;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot") TSubclassOf<AEnemyMaster> EnemyClass;
};
//-----------------------------------------------------------------------------------------------------------