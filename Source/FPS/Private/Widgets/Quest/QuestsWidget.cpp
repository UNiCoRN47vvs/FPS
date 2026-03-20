#include "Widgets/Quest/QuestsWidget.h"
#include "Widgets/Quest/QuestButtonWidget.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "FPS/FPSCharacter.h"
#include "Interact/NPC/NPC.h"
#include "ActorComponents/Quest/PlayerQuestComponent.h"
#include "ActorComponents/Quest/QuestGiverComponent.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Widgets/Quest/QuestRewardWidget.h"
#include "Config/QuestMasterDA.h"
#include "Config/UseQuestTargetDA.h"
#include "Struct/QuestStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UQuestsWidget::InitQuestWidget(UPlayerQuestComponent* playerQuestComponent, AActor* questGiverActor, UMainHUDWidget* mainHUDWidget)
{
	bool bIsSuccess = false;

	QuestComponent = playerQuestComponent;
	QuestGiver = Cast<ANPC>(questGiverActor);
	MainHUD = mainHUDWidget;

	PTR(QuestApplyButton)->SetVisibility(ESlateVisibility::Collapsed);
	PTR(QuestPassButton)->SetVisibility(ESlateVisibility::Collapsed);

	bIsSuccess = ReactivateWidget();
	if (!bIsSuccess)
		return;

	QuestApplyButton->Button->OnClicked.AddDynamic(this, &UQuestsWidget::ClickQuestApplyButton);
	QuestPassButton->Button->OnClicked.AddDynamic(this, &UQuestsWidget::ClickQuestPassButton);
}
//-----------------------------------------------------------------------------------------------------------
void UQuestsWidget::InitQuestWidget(UPlayerQuestComponent* playerQuestComponent, UMainHUDWidget* mainHUDWidget)
{
	QuestComponent = playerQuestComponent;
	MainHUD = mainHUDWidget;

	PTR(QuestApplyButton)->SetVisibility(ESlateVisibility::Collapsed);
	PTR(QuestPassButton)->SetVisibility(ESlateVisibility::Collapsed);

	bool bIsFirst = true;
	UQuestButtonWidget* buttonWidget = nullptr;
	

	CHECK_PTR(QuestComponent)

	const TArray<FQuest>& availableQuests = QuestComponent->GetCurrentQuests();

	if (availableQuests.IsEmpty())
		return;

	for (const FQuest& item : availableQuests)
	{
		buttonWidget = CreateWidget<UQuestButtonWidget>(this, QuestButtonClass);
		if (!buttonWidget)
		{
			ALARM_LOG
			continue;
		}

		ListQuestsSB->AddChild(buttonWidget);
		buttonWidget->InitQuestButton(item);
		buttonWidget->OnButtonWidgetClick.AddUObject(this, &UQuestsWidget::SetActiveQuest);

		if (bIsFirst)
		{
			buttonWidget->ButtonClick();
			bIsFirst = false;
		}
	}

	return;
}
//-----------------------------------------------------------------------------------------------------------
void UQuestsWidget::SetActiveQuest(FQuest quest)
{
	UQuestRewardWidget* rewadWidget = nullptr;
	WrapBox->ClearChildren();
	TextDescriptionTB->SetText(FText::GetEmpty());
	TextRewardTB->SetText(FText::GetEmpty());
	TextGoalCurrentTB->SetText(FText::GetEmpty());
	TextGoalMaxTB->SetText(FText::GetEmpty());
	HeaderQuestNameTB->SetText(FText::GetEmpty());

	QuestStruct = quest;
	CHECK_PTR(QuestStruct.QuestMasterDA)

	QuestApplyButton->SetVisibility(ESlateVisibility::Collapsed);
	QuestPassButton->SetVisibility(ESlateVisibility::Collapsed);

	QuestStruct.MaxCount > 0 ? QuestPassButton->SetVisibility(ESlateVisibility::Visible) : QuestApplyButton->SetVisibility(ESlateVisibility::Visible);
	
	HeaderQuestNameTB->SetText(QuestStruct.QuestMasterDA->QuestName);
	TextGoalCurrentTB->SetText(FText::AsNumber(QuestStruct.CurrentCount));
	TextGoalMaxTB->SetText(FText::AsNumber(QuestStruct.QuestMasterDA->QuestMaxCount));
	TextDescriptionTB->SetText(QuestStruct.QuestMasterDA->QuestDescription);
	TextRewardTB->SetText(FText::AsNumber(QuestStruct.QuestMasterDA->QuestReward.CurrencyReward.Sulfur));

	for (const FItemReward& item : QuestStruct.QuestMasterDA->QuestReward.ItemRewards)
	{
		rewadWidget = CreateWidget<UQuestRewardWidget>(this, QuestRewardClass);
		if (!rewadWidget)
		{
			ALARM_LOG
			continue;
		}

		WrapBox->AddChild(rewadWidget);
		rewadWidget->InitRewardWidget(item);
	}

	if (!QuestGiver)
	{
		QuestApplyButton->SetVisibility(ESlateVisibility::Collapsed);
		QuestPassButton->SetVisibility(ESlateVisibility::Collapsed);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UQuestsWidget::ClickQuestApplyButton()
{
	CHECK_PTR(QuestComponent)

	bool bIsPickUpSuccess = false;
	int32 itemCount = 1;
	AFPSCharacter* playerCharacter = nullptr;
	UUseQuestTargetDA* useQuestInteractDA = nullptr;
	TArray<UUseQuestTargetDA*> useQuestInteractArray = {};

	CHECK_PTR(QuestStruct.QuestMasterDA)
	for (TSoftObjectPtr<UPrimaryDataAsset> item : QuestStruct.QuestMasterDA->QuestTarget)
	{
		useQuestInteractDA = Cast<UUseQuestTargetDA>(item.LoadSynchronous());
		if (!useQuestInteractDA)
			continue;

		useQuestInteractArray.Add(useQuestInteractDA);
	}

	if (!useQuestInteractArray.IsEmpty())
	{
		playerCharacter = QuestComponent->GetOwner<AFPSCharacter>();
		CHECK_PTR(playerCharacter)

		if (!playerCharacter->DoesHasEmptySlots(useQuestInteractArray.Num()))
			return; //TODO : Отобразить что квест не взялся из-за недостатка места в инвентаре под квестовый предмет
		
		for (UUseQuestTargetDA* item : useQuestInteractArray)
		{
			playerCharacter->PickUpItem(itemCount, item->ItemDA);
		}
	}

	QuestComponent->AddNewQuest(QuestStruct);
	PlaySound(QuestApplySound);
	ListQuestsSB->ClearChildren();
	ReactivateWidget();
}
//-----------------------------------------------------------------------------------------------------------
void UQuestsWidget::ClickQuestPassButton()
{
	if (QuestStruct.CurrentCount < QuestStruct.MaxCount) //TODO : Добавить обозначение что квест еще не выолнен
		return;

	bool bIsSuccess = false;
	int32 itemCount = 0;
	AFPSCharacter* character = QuestComponent->GetOwner<AFPSCharacter>();
	CHECK_PTR(character)
	CHECK_PTR(QuestStruct.QuestMasterDA)

	character->PickUpCurrency(QuestStruct.QuestMasterDA->QuestReward.CurrencyReward);
	for (auto& item : QuestStruct.QuestMasterDA->QuestReward.ItemRewards)
	{
		itemCount = item.ItemCount;
		character->PickUpItem(itemCount, item.ItemDA.LoadSynchronous());
	}

	QuestComponent->QuestComplete(QuestStruct);
	ListQuestsSB->ClearChildren();

	PlaySound(QuestCompleteSound);

	bIsSuccess = ReactivateWidget();

	if (!bIsSuccess && GetOwningPlayer())
	{
		GetOwningPlayer()->bShowMouseCursor = false;
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->SetPause(false);
		RemoveFromParent();
	}
}
//-----------------------------------------------------------------------------------------------------------
bool UQuestsWidget::ReactivateWidget()
{
	bool bIsFirst = true;
	UQuestButtonWidget* buttonWidget = nullptr;
	TArray<FQuest> availableQuests = {};

	if (QuestGiver && QuestGiver->GetQuestGiverComponent())
		availableQuests = QuestGiver->GetQuestGiverComponent()->GetAllAvailableQuests(QuestComponent);
	else if (QuestComponent)
		availableQuests = QuestComponent->GetCurrentQuests();

	if (availableQuests.IsEmpty())
		return false;

	for (const FQuest& item : availableQuests)
	{
		buttonWidget = CreateWidget<UQuestButtonWidget>(this, QuestButtonClass);
		if (!buttonWidget)
		{
			ALARM_LOG
			continue;
		}

		ListQuestsSB->AddChild(buttonWidget);
		buttonWidget->InitQuestButton(item);
		buttonWidget->OnButtonWidgetClick.AddUObject(this, &UQuestsWidget::SetActiveQuest);

		if (bIsFirst)
		{
			buttonWidget->ButtonClick();
			bIsFirst = false;
		}
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------