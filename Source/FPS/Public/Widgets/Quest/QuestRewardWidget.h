#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "QuestRewardWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UItemMasterDA;
class UTextBlock;
class USlotWidget;
struct FItemReward;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestRewardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitRewardWidget(const FItemReward& item);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward Widget", meta = (BindWidget)) USlotWidget* RewardSlot;
};
//-----------------------------------------------------------------------------------------------------------