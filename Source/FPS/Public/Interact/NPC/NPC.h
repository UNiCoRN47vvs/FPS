#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/ItemInteract.h"
#include "Interfaces/InteractInfo.h"
#include "Interfaces/DropInterface.h"
#include "NPC.generated.h"
//-----------------------------------------------------------------------------------------------------------
class ACharacterMaster;
class UNPCStorageComponent;
class UQuestGiverComponent;
class UNPCDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ANPC : public APawn, public IItemInteract, public IInteractInfo
{
	GENERATED_BODY()

public:
	ANPC();
	//**************************
	//Interface
	virtual void InteractWithActor(ACharacterMaster* playerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;
	//**************************
	//Getters
	TWeakObjectPtr<UNPCStorageComponent> GetNPCStorageComponent();
	UQuestGiverComponent* GetQuestGiverComponent();
	//**************************

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC") UNPCDA* NPCDA;
private:
	void InitStore();
	UPROPERTY() TWeakObjectPtr<UNPCStorageComponent> StorageComponent;
	UPROPERTY() UQuestGiverComponent* QuestGiverComponent;

};
//-----------------------------------------------------------------------------------------------------------