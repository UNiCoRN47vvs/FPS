#pragma once

#include "FPS/FPS.h"
#include "Components/ActorComponent.h"
#include "QuestMasterComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UQuestMasterComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UQuestMasterComponent();
	
protected:
	virtual void BeginPlay() override;


};
//-----------------------------------------------------------------------------------------------------------