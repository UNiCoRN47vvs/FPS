#include "Widgets/MainMenu/LoadGameWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Save/MasterSave.h"
#include "Widgets/MainMenu/DeleteSaveGameWidget.h"
#include "Widgets/MainMenu/SignboardWidget.h"
//-----------------------------------------------------------------------------------------------------------
void ULoadGameWidget::InitLoadGameWidget(UMasterSave* MasterSave)
{
	CHECK_PTR(MasterSave)
	UDeleteSaveGameWidget* widget = nullptr;

	for (auto& item : MasterSave->MasterSave)
	{
		widget = CreateWidget<UDeleteSaveGameWidget>(GetWorld(), WBPDeleteSaveGameWidget.Get());

		if (!widget)
		{
			ALARM_LOG
			continue;
		}

		ScrollBox->AddChild(widget);
		widget->SignboardWidget->TextTB->SetText(FText::FromString(item.Key));
	}
}
//-----------------------------------------------------------------------------------------------------------
void ULoadGameWidget::ClearLoadGameWidget()
{
	ScrollBox->ClearChildren();
}
