#pragma once

#include "Widgets/Inventory/InventoryButtonWidget.h"
#include "Struct/QuestStruct.h"
#include "QuestButtonWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UQuestMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestButtonWidget : public UInventoryButtonWidget
{
	GENERATED_BODY()
public:
	void InitQuestButton(const FQuest& questStruct);
	UFUNCTION() void ButtonClick();

	TMulticastDelegate<void(FQuest)> OnButtonWidgetClick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Button Widget") FSlateColor ActiveQuestColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Button Widget") FSlateColor ReadyQuestColor;
	UPROPERTY() FQuest Quest;

protected:
	virtual void BeginDestroy() override;
};
//-----------------------------------------------------------------------------------------------------------