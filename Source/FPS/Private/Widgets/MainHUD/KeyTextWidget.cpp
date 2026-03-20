#include "Widgets/MainHUD/KeyTextWidget.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/TextBlock.h"
#include "Subsystem/EventBus.h"
//-----------------------------------------------------------------------------------------------------------
void UKeyTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UEventBus::OnUpdateKeyInfo.AddUObject(this, &UKeyTextWidget::UpdateInfo);
	
	if (!UEventBus::OnGetKeyInfo.IsBound())
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UKeyTextWidget::UpdateInfo);
	else
		UpdateInfo();
}
//-----------------------------------------------------------------------------------------------------------
void UKeyTextWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UEventBus::OnUpdateKeyInfo.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
void UKeyTextWidget::UpdateInfo()
{
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
			if (subItem.GetSlot() == EPlayerMappableKeySlot::First && subItem.GetMappingName() == MappingName)
			{
				if (!UEventBus::OnGetKeyInfo.IsBound())
					return;

				const TMap<FKey, FText>& keyInfo = UEventBus::OnGetKeyInfo.Execute();

				if (keyInfo.Contains(subItem.GetCurrentKey()))
				{
					PTR(TextBlock)->SetText(*keyInfo.Find(subItem.GetCurrentKey()));
					return;
				}

				PTR(TextBlock)->SetText(FText::FromName(subItem.GetCurrentKey().GetFName()));

				return;
			}
		}

	}
}
//-----------------------------------------------------------------------------------------------------------