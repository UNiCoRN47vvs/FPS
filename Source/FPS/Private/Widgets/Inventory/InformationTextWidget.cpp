#include "Widgets/Inventory/InformationTextWidget.h"
#include "Components/TextBlock.h"
//-----------------------------------------------------------------------------------------------------------
void UInformationTextWidget::InitValueText(FText Text)
{
	ValueTB->SetText(Text);
}
bool UInformationTextWidget::IsTextEmpty()
{
	return ValueTB->GetText().IsEmpty();
}
//-----------------------------------------------------------------------------------------------------------