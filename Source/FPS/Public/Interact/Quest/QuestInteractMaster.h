#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Actor.h"
#include "Config/QuestInteractTargetMasterDA.h"
#include "QuestInteractMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AQuestInteractMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestInteractMaster();
	
	virtual void InitInteractQuest();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_I_M") UQuestInteractTargetMasterDA* QuestInteractDA;
protected:
	virtual void BeginPlay() override;

};
//-----------------------------------------------------------------------------------------------------------