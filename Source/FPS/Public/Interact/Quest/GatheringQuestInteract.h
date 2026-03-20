#pragma once

#include "Interact/Quest/QuestInteractMaster.h"
#include "Interfaces/ItemInteract.h"
#include "Interfaces/InteractInfo.h"
#include "Interact/InteractMaster.h"
#include "GatheringQuestInteract.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AGatheringQuestInteract : public AQuestInteractMaster, public IItemInteract, public IInteractInfo
{
	GENERATED_BODY()
public:
	AGatheringQuestInteract();
	virtual void InitInteractQuest() override;
	//**************************
	//Interface
	virtual void InteractWithActor(ACharacterMaster* playerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;
	//**************************
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Q_I_M") USkeletalMeshComponent* SkeletalMeshComponent;
};
//-----------------------------------------------------------------------------------------------------------