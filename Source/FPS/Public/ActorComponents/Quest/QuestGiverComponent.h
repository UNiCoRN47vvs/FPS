#pragma once

#include "ActorComponents/Quest/QuestMasterComponent.h"
#include "Struct/QuestStruct.h"
#include "QuestGiverComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UPlayerQuestComponent;
class UQuestsDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestGiverComponent : public UQuestMasterComponent
{
	GENERATED_BODY()
	
public:
	UQuestGiverComponent();
	TArray<FQuest> GetAllAvailableQuests(UPlayerQuestComponent* playerQuestComp);
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_G_C") int32 QuestMaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_G_C") FString FolderPath;
protected:
	void BeginDestroy() override;
	void LoadAllQuestDataAssetsFromPath();
};
//-----------------------------------------------------------------------------------------------------------