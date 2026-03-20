#include "Widgets/MainMenu/ControlSettingsWidget.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/VerticalBox.h"
#include "Widgets/MainMenu/ControlSettingsBoxWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UControlSettingsWidget::InitControlWidget()
{
	VerticalBox->ClearChildren();

	UControlSettingsBoxWidget* boxWidget = nullptr;
	UEnhancedInputLocalPlayerSubsystem* subsystem = nullptr;
	UEnhancedInputUserSettings* inputUserSettings = nullptr;
	TArray<FKeyMappingRow> outArray = {};

	subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayer()->GetLocalPlayer());
	CHECK_PTR(subsystem)

	inputUserSettings = subsystem->GetUserSettings();
	CHECK_PTR(inputUserSettings)
		
	inputUserSettings->GetCurrentKeyProfile()->GetPlayerMappingRows().GenerateValueArray(outArray);

	for (const FKeyMappingRow& item : outArray)
	{
		for (const FPlayerKeyMapping& subItem : item.Mappings)
		{
			if (subItem.GetSlot() == EPlayerMappableKeySlot::First)
			{
				boxWidget = CreateWidget<UControlSettingsBoxWidget>(GetWorld(), BoxWidget);
				if (!boxWidget)
				{
					ALARM_LOG
					continue;
				}
				VerticalBox->AddChild(boxWidget);
				boxWidget->InitBox(subItem.GetMappingName(), subItem.GetDisplayName(), subItem.GetCurrentKey());

				break;
			}
		}
		
	}
}
//-----------------------------------------------------------------------------------------------------------
