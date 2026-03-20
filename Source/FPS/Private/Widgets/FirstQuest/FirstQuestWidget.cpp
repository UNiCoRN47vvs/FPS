#include "Widgets/FirstQuest/FirstQuestWidget.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Widgets/GeneralCenterWidget/GeneralCenterWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UFirstQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsValid(MainHUD) && IsValid(MainHUD->WBPGeneralCenter))
		RemoveFromParent();
}
//-----------------------------------------------------------------------------------------------------------
void UFirstQuestWidget::InitFirstQuest(UMainHUDWidget* mainHUD)
{
	MainHUD = mainHUD;
	CHECK_PTR(MainHUD)
}
//-----------------------------------------------------------------------------------------------------------
