#include "Widgets/ProgressBar/ProgressBarWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UProgressBarWidget::SetValueProgressBar(double CurrentValue, double MaxValue)
{
	FString LocalCurrent = FString::FormatAsNumber(CurrentValue);
	FString LocalMax = FString::FormatAsNumber(MaxValue);

	ProgressBar->SetPercent(CurrentValue / MaxValue);
	ValueTextBlock->SetText(FText::FromString(LocalCurrent + "/" + LocalMax));
}
//-----------------------------------------------------------------------------------------------------------