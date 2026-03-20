#include "Widgets/Quest/QuestButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Config/QuestMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UQuestButtonWidget::InitQuestButton(const FQuest& questStruct)
{
	FButtonStyle buttonStyle = {};
	Quest = questStruct;

	CHECK_PTR(Quest.QuestMasterDA)
	CHECK_PTR(TextBlock)
	CHECK_PTR(Button)

	TextBlock->SetText(Quest.QuestMasterDA->QuestName);

	if (Quest.MaxCount > 0)
	{
		buttonStyle = Button->GetStyle();

		if (Quest.CurrentCount >= Quest.MaxCount)
			buttonStyle.Normal.OutlineSettings.Color = ReadyQuestColor;
		else
			buttonStyle.Normal.OutlineSettings.Color = ActiveQuestColor;

		Button->SetStyle(buttonStyle);
	}

	Button->OnClicked.AddDynamic(this, &UQuestButtonWidget::ButtonClick);
}
//-----------------------------------------------------------------------------------------------------------
void UQuestButtonWidget::ButtonClick()
{
	OnButtonWidgetClick.Broadcast(Quest);
}
//-----------------------------------------------------------------------------------------------------------
void UQuestButtonWidget::BeginDestroy()
{
	Super::BeginDestroy();
	OnButtonWidgetClick.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
