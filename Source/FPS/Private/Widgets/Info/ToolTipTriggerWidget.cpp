#include "Widgets/Info/ToolTipTriggerWidget.h"
#include "Subsystem/EventBus.h"
#include "Widgets/Inventory/InformationWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UToolTipTriggerWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (!UEventBus::OnShowInformationStateWidget.IsBound() || !UEventBus::OnGetPlayerStateMap.IsBound())
		return;

	TMap<EStateName, float>& stateMap = UEventBus::OnGetPlayerStateMap.Execute();

	SetToolTip(UEventBus::OnShowInformationStateWidget.Execute(stateMap));
}
//-----------------------------------------------------------------------------------------------------------