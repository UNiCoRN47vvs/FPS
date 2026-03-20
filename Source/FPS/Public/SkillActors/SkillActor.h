#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Actor.h"
#include "Enums/ElementsType.h"
#include "Struct/StatRange.h"
#include "Struct/DamageStruct.h"
#include "SkillActor.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UNiagaraComponent;
class USkillScrollDA;
class USkillAttackDA;
class UEnemyMasterDA;
class AEnemyMaster;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ASkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillActor();
	virtual void InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA);
	virtual void InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner);
	virtual void InitParam(float damage, UEnemyMasterDA* enemyMasterDA, AEnemyMaster* enemy, USkillAttackDA* skillDA = nullptr);
	virtual void ActivateSkill();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "S_A") UNiagaraComponent* NiagaraComponent;

protected:
	virtual void BeginPlay() override;
	FDamageStruct DamageStruct;

	UFUNCTION() void DestroyAfterNiagara(class UNiagaraComponent* PSystem);
private:

};
//-----------------------------------------------------------------------------------------------------------