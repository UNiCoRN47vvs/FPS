#pragma once

#include "FPS/FPS.h"
#include "DetourCrowdAIController.h"
#include "EnemyAIController.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AEnemyMaster;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class FPS_API AEnemyAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()
public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY() AEnemyMaster* EnemyCharacter;
};
//-----------------------------------------------------------------------------------------------------------