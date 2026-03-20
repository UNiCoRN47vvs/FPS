#include "Widgets/Info/InformationStandWidget.h"
#include "Components/ScrollBox.h"
#include "Widgets/Info/StandButtonWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UInformationStandWidget::InitInformationStand()
{
	UStandButtonWidget* widget = nullptr;
	ListInfoSB->ClearChildren();

	for (const auto& item : InfoMap)
	{
		widget = CreateWidget<UStandButtonWidget>(GetWorld(), ButtonWidgetClass);
		if (!widget)
			continue;

		ListInfoSB->AddChild(widget);
		widget->InitStandButton(item.Key);
		widget->OnStandButtonClick.BindUObject(this, &UInformationStandWidget::StandButtonClick);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInformationStandWidget::StandButtonClick(const FName& name)
{
	TSubclassOf<UUserWidget> widgetClass = {};

	if (!InfoMap.Contains(name))
		return;
	
	widgetClass = *InfoMap.Find(name);

	InfoSB->ClearChildren();
	InfoWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

	CHECK_PTR(InfoWidget)

	InfoSB->AddChild(InfoWidget);
}
//-----------------------------------------------------------------------------------------------------------
