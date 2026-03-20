#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Enums/EnemySkillType.h"
#include "Struct/EnemySkillsData.h"
#include "AIBrainComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AEnemyMaster;
class AEnemyAIController;
class UEnemyMasterDA;
class AFPSGameMode;
class UEnemySC;
class UNavigationSystemV1;
class ANavigationData;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UAIBrainComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAIBrainComponent();
	void AITrigger(APawn* Pawn);
	void InitAIBrain(AEnemyMaster* EnemyMaster, UEnemyMasterDA* EnemyMasterDA);
	void MoveToRandomPoint();
	void SkillImpact(EEnemySkillType skillType, float value);
	UEnemySC* GetEnemySC();

	UFUNCTION() void AttackEnded();
	UFUNCTION() void AttackAfterMove();

	uint8 bHasTarget : 1;
	uint8 bIsMoving : 1;
	uint8 bIsAttacking : 1;
	uint8 bSkillIsActive : 1;

	UPROPERTY() APawn* PawnTarget;
	UPROPERTY() UEnemyMasterDA* EnemyDA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Brain Component") float MovementInterval;
	FVector RandomLocation;
	FEnemySkillsData CurrentEnemySkill;
protected:
	bool AICharacterIsValid();
	bool AIControllerIsValid();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginDestroy() override;
	FEnemySkillsData EnemySkillChoice();


	UPROPERTY() AEnemyMaster* AICharacter;
	UPROPERTY() AEnemyAIController* AIController;
	UPROPERTY() UEnemySC* EnemySC;
	UPROPERTY() float AttackDistance;
private:
	FEnemySkillsData GetTier1Skill();
	void AITriggerSubFunc();
	FVector GetRandomLocationInRadius(float Radius);
	void CheckOpportunityAttack();

	float SkillDistance;
	float TimeSinceLastAction;
	UPROPERTY() TMap<EEnemySkillType, float> SkillsTypeValue;
	UPROPERTY() AFPSGameMode* GameMode;
	UPROPERTY() ANavigationData* UseNavData;
	UPROPERTY() UNavigationSystemV1* NavSys;
	UPROPERTY() FTimerHandle TriggetFollowHandle;
};
//-----------------------------------------------------------------------------------------------------------