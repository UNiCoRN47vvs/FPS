#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Struct/QuestStruct.h"
#include "QuestsWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UVerticalBox;
class UHorizontalBox;
class UScrollBox;
class UTextBlock;
class UQuestButtonWidget;
class UPlayerQuestComponent;
class UQuestMasterDA;
class UQuestRewardWidget;
class ANPC;
class UButton;
class UMainHUDWidget;
class UWrapBox;
struct FQuest;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitQuestWidget(UPlayerQuestComponent* playerQuestComponent, AActor* questGiverActor, UMainHUDWidget* mainHUDWidget);
	void InitQuestWidget(UPlayerQuestComponent* playerQuestComponent, UMainHUDWidget* mainHUDWidget);

	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UHorizontalBox* HeaderQuestsHB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UScrollBox* ListQuestsSB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UTextBlock* TextDescriptionTB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UTextBlock* TextRewardTB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UTextBlock* TextGoalCurrentTB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UTextBlock* TextGoalMaxTB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UTextBlock* HeaderQuestNameTB;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UQuestButtonWidget* QuestApplyButton;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UQuestButtonWidget* QuestPassButton;
	UPROPERTY(BlueprintReadOnly, Category = "Q_W", meta = (BindWidget)) UWrapBox* WrapBox;


protected:
	bool ReactivateWidget();
	UFUNCTION() void SetActiveQuest(FQuest quest);
	UFUNCTION() void ClickQuestApplyButton();
	UFUNCTION() void ClickQuestPassButton();
	UPROPERTY() FQuest QuestStruct;
private:
	UPROPERTY(EditAnywhere, Category = "Q_W") TSubclassOf<UQuestButtonWidget> QuestButtonClass;
	UPROPERTY(EditAnywhere, Category = "Q_W") TSubclassOf<UQuestRewardWidget> QuestRewardClass;
	UPROPERTY(EditAnywhere, Category = "Q_W") USoundWave* QuestApplySound;
	UPROPERTY(EditAnywhere, Category = "Q_W") USoundWave* QuestCompleteSound;
	UPROPERTY() UPlayerQuestComponent* QuestComponent;
	UPROPERTY() ANPC* QuestGiver;
	UPROPERTY() UMainHUDWidget* MainHUD;
};
//-----------------------------------------------------------------------------------------------------------