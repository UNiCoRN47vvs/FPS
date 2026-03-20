#include "Widgets/Inventory/InformationWidget.h"
#include "Components/VerticalBox.h"
#include "SubSystem/EventBus.h"
#include "Struct/ItemInvStruct.h"
#include "Widgets/Inventory/InformationTextWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ClearParams();

	UEventBus::OnShowInformationWidget.BindUObject(this, &UInformationWidget::InitParams);
	UEventBus::OnShowInformationStateWidget.BindUObject(this, &UInformationWidget::InitParams);
}
//-----------------------------------------------------------------------------------------------------------
void UInformationWidget::NativeDestruct()
{
	Super::NativeDestruct();
	UEventBus::OnShowInformationWidget.Unbind();
	UEventBus::OnShowInformationStateWidget.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
UInformationWidget* UInformationWidget::InitParams(FItemInvStruct itemData)
{
	UVerticalBox* verticalBox = VB1;
	int32 counter = 0;
	UInformationTextWidget* informTextWidget = nullptr;
	FText infoText = {};
	ClearParams();

	if (!itemData.ItemDA)
	{
		ALARM_LOG
		return nullptr;
	}

	for (auto& item : itemData.GetItemInfo())
	{
		informTextWidget = CreateWidget<UInformationTextWidget>(this, InformTextWidgetClass);
		if (!informTextWidget)
			continue;

		verticalBox->AddChild(informTextWidget);

		infoText = FText::Format(FText::FromString("{0}{1}{2}"), FText::FromString(item.Key), FText::FromString(TEXT(" : ")), item.Value);
		informTextWidget->InitValueText(infoText);

		++counter;

		switch (counter)
		{
		case 6 :
			verticalBox = VB2;
			if(verticalBox)
				verticalBox->SetVisibility(ESlateVisibility::Visible);
			break;

		case 12 :
			verticalBox = VB3;
			if (verticalBox)
				verticalBox->SetVisibility(ESlateVisibility::Visible);
			break;

		case 18 :
			verticalBox = VB4;
			if (verticalBox)
				verticalBox->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			break;
		}
	}

	return this;
}
//-----------------------------------------------------------------------------------------------------------
UInformationWidget* UInformationWidget::InitParams(TMap<EStateName, float>& stateMap)
{
	UVerticalBox* verticalBox = VB1;
	int32 counter = 0;
	UInformationTextWidget* informTextWidget = nullptr;
	FText infoText{};
	FText enumText{};
	ClearParams();

	for (auto& item : stateMap)
	{
		informTextWidget = CreateWidget<UInformationTextWidget>(this, InformTextWidgetClass);
		if (!informTextWidget)
			continue;

		verticalBox->AddChild(informTextWidget);

		ENUM_TO_TEXT(item.Key, EStateName, enumText)

		infoText = FText::Format(FText::FromString("{0}{1}{2}"), enumText, FText::FromString(TEXT(" : ")), item.Value);
		informTextWidget->InitValueText(infoText);

		++counter;

		switch (counter)
		{
		case 10:
			verticalBox = VB2;
			if (verticalBox)
				verticalBox->SetVisibility(ESlateVisibility::Visible);
			break;

		case 20:
			verticalBox = VB3;
			if (verticalBox)
				verticalBox->SetVisibility(ESlateVisibility::Visible);
			break;

		case 30:
			verticalBox = VB4;
			if (verticalBox)
				verticalBox->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			break;
		}
	}

	return this;
}
//-----------------------------------------------------------------------------------------------------------
void UInformationWidget::ClearParams()
{
	VB1->ClearChildren();
	VB2->ClearChildren();
	VB3->ClearChildren();
	VB4->ClearChildren();
}
//-----------------------------------------------------------------------------------------------------------

