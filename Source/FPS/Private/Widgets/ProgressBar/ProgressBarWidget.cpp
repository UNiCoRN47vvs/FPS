#include "Widgets/ProgressBar/ProgressBarWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UProgressBarWidget::SetValueProgressBar(float currentValue, float maxValue)
{
	FString current = FString::FormatAsNumber(currentValue);
	FString max = FString::FormatAsNumber(maxValue);

	ProgressBar->SetPercent(currentValue / maxValue);
	ValueTextBlock->SetText(FText::FromString(current + "/" + max));
}
//-----------------------------------------------------------------------------------------------------------