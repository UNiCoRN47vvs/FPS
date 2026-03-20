#include "Widgets/MainHUD/FramePerSecondWidget.h"
#include "Components/TextBlock.h"
//-----------------------------------------------------------------------------------------------------------
void UFramePerSecondWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MaxTime = 0.5;
}
