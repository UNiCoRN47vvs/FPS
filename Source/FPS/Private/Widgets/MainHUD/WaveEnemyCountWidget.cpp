#include "Widgets/MainHUD/WaveEnemyCountWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
//-----------------------------------------------------------------------------------------------------------
void UWaveEnemyCountWidget::UpdateTimeCount(int32 Count)
{
	if (Count <= 0)
	{
		TimeCount->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	TimeCount->SetVisibility(ESlateVisibility::Visible);

	TimeCount->SetText(FText::AsNumber(Count));
}
//-----------------------------------------------------------------------------------------------------------
void UWaveEnemyCountWidget::UpdateWaveCount(int32 Count)
{
	if (Count <= 0)
	{
		CountBorder->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	CountBorder->SetVisibility(ESlateVisibility::Visible);

	WaveCount->SetText(FText::AsNumber(Count));
}
//-----------------------------------------------------------------------------------------------------------
void UWaveEnemyCountWidget::UpdateEnemyCount(int32 Count)
{
	EnemyCount->SetText(FText::AsNumber(Count));
}
//-----------------------------------------------------------------------------------------------------------