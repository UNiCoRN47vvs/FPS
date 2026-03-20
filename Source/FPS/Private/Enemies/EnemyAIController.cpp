#include "Enemies/EnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Enemies/EnemyMaster.h"
//-----------------------------------------------------------------------------------------------------------
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	UCrowdFollowingComponent* crowdComponent = FindComponentByClass<UCrowdFollowingComponent>();
	CHECK_PTR(crowdComponent)

	crowdComponent->SetCrowdSeparation(true);
	crowdComponent->SetCrowdSeparationWeight(300.0);
	crowdComponent->SetCrowdAvoidanceRangeMultiplier(0.5);
}
//-----------------------------------------------------------------------------------------------------------
void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	CHECK_CAST(EnemyCharacter, AEnemyMaster, GetPawn())

	switch (Result.Code)
	{
	case EPathFollowingResult::Success :
		EnemyCharacter->AttackAfterMove();
		break;

	case EPathFollowingResult::OffPath : //TODO : Добавить телепортацию на навмеш
	case EPathFollowingResult::Invalid : //Если цель вне досегаемости пути
	case EPathFollowingResult::Aborted :
	case EPathFollowingResult::Blocked :
		EnemyCharacter->Reactivate();
		break;

	default:
		Destroy();
		ALARM_LOG
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------