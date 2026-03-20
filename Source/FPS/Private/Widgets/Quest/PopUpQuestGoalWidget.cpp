#include "Widgets/Quest/PopUpQuestGoalWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Config/QuestMasterDA.h"
#include "Struct/QuestStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UPopUpQuestGoalWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
//-----------------------------------------------------------------------------------------------------------
void UPopUpQuestGoalWidget::InitPopUpQuestGoal(const FQuest& QuestStruct)
{
	if (!QuestStruct.QuestMasterDA)
	{
		ALARM_LOG
		RemoveFromParent();
		return;
	}

	CurrentGoalTB->SetText(FText::AsNumber(QuestStruct.CurrentCount));
	QuestMaxGoalTB->SetText(FText::AsNumber(QuestStruct.MaxCount));
	NameTB->SetText(QuestStruct.QuestMasterDA->QuestName);

	if (QuestStruct.CurrentCount >= QuestStruct.MaxCount)
		Image->SetVisibility(ESlateVisibility::Visible);
}
//-----------------------------------------------------------------------------------------------------------


