#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "EnemyStateComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UNiagaraComponent;
class AEnemyMaster;
class USkillDefenseDA;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FDefenseSkill
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "D_S") float LifeTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "D_S") UNiagaraComponent* NiagaraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "D_S") TWeakObjectPtr<USkillDefenseDA> SkillDA;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UEnemyStateComponent : public UStateMasterComponent
{
	GENERATED_BODY()
public:
	UEnemyStateComponent();
	virtual void AuraEffect(USkillDefenseDA* SkillDA) override;
	void SetEnemyStateMap(const TMap<EStateName, float>& enemyStateMap);
	void UseDefenseSkill(UNiagaraComponent* NiagaraComponent, USkillDefenseDA* SkillDA);
	bool IsDefenseSkillActive();
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	AEnemyMaster* GetEnemyOwner();
	void ApplyDefenseSkill(USkillDefenseDA* SkillDA);
	void ApplyStateAura(bool bIsActiveAura);
	void ApplySkillBuff();

	float CheckInterval;
	UPROPERTY() AEnemyMaster* EnemyCharacter;
	UPROPERTY() FTimerHandle BuffTimer;
	UPROPERTY() FDefenseSkill DefenseSkill;
	UPROPERTY() FDefenseSkill AuraSkill;
};
//-----------------------------------------------------------------------------------------------------------