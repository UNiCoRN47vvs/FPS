#include "Widgets/Info/InfoButtonWidget.h"
#include "Subsystem/EventBus.h"
#include "Components/Button.h"
#include "FirstPerson/FPSGameInstance.h"
#include "Save/MasterSave.h"
//-----------------------------------------------------------------------------------------------------------
void UInfoButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PTR(InfoButton)->OnClicked.AddDynamic(this, &UInfoButtonWidget::UseInfoButton);

	if (!UEventBus::OnGetSaveInfoMap.IsBound())
		return;

	TMap<FName, bool>& infoMap = UEventBus::OnGetSaveInfoMap.Execute();

	if (infoMap.Contains(InfoNameWidget))
		return;

	PlayAnimation(FirstAnimation, 0.0f, 0);
}
//-----------------------------------------------------------------------------------------------------------
void UInfoButtonWidget::UseInfoButton()
{
	UEventBus::OnClickInfoButton.ExecuteIfBound(InfoNameWidget);

	if (!UEventBus::OnGetSaveInfoMap.IsBound())
		return;

	TMap<FName, bool>& infoMap = UEventBus::OnGetSaveInfoMap.Execute();

	if (infoMap.Contains(InfoNameWidget))
		return;

	infoMap.Add(InfoNameWidget, true);
}
//-----------------------------------------------------------------------------------------------------------
