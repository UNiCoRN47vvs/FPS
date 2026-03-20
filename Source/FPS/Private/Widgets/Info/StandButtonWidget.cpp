#include "Widgets/Info/StandButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
//-----------------------------------------------------------------------------------------------------------
void UStandButtonWidget::InitStandButton(const FName& name)
{
	TextBlock->SetText(FText::FromName(name));

	Button->OnClicked.AddDynamic(this, &UStandButtonWidget::StandButtonClick);

	Name = name;
}
//-----------------------------------------------------------------------------------------------------------
void UStandButtonWidget::StandButtonClick()
{
	OnStandButtonClick.ExecuteIfBound(Name);
}
//-----------------------------------------------------------------------------------------------------------
