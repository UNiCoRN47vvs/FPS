#pragma once

#include "Widgets/PopUp/PopUpMasterWidget.h"
#include "PopUpQuestGoalWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
struct FQuest;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPopUpQuestGoalWidget : public UPopUpMasterWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitPopUpQuestGoal(const FQuest& QuestStruct);
	
	UPROPERTY(BlueprintReadOnly, Category = "PopUp", meta = (BindWidget)) UTextBlock* QuestMaxGoalTB;
};
//-----------------------------------------------------------------------------------------------------------