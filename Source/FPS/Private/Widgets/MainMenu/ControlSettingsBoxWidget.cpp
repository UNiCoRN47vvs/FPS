#include "Widgets/MainMenu/ControlSettingsBoxWidget.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "Components/TextBlock.h"
#include "Components/InputKeySelector.h"
#include "Subsystem/EventBus.h"
//-----------------------------------------------------------------------------------------------------------
void UControlSettingsBoxWidget::InitBox(const FName& mappingName, const FText& text, const FKey& key)
{
	FInputChord inputChord = {};
	inputChord.Key = key;

	PTR(TextBlock)->SetText(text);
	PTR(InputKeySelector)->SetSelectedKey(inputChord);

	MappingName = mappingName;

	InputKeySelector->OnKeySelected.AddDynamic(this, &UControlSettingsBoxWidget::SetBoxInformation);
}
//-----------------------------------------------------------------------------------------------------------
void UControlSettingsBoxWidget::SetBoxInformation(FInputChord inputChord)
{
	UEnhancedInputLocalPlayerSubsystem* subsystem = nullptr;
	UEnhancedInputUserSettings* inputUserSettings = nullptr;
	FGameplayTagContainer tagContainer = {};
	FMapPlayerKeyArgs playerKeyArgs = {};

	subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayer()->GetLocalPlayer());
	CHECK_PTR(subsystem)

	inputUserSettings = subsystem->GetUserSettings();
	CHECK_PTR(inputUserSettings)

	PTR(InputKeySelector)->SetSelectedKey(inputChord);

	playerKeyArgs.MappingName = MappingName;
	playerKeyArgs.Slot = EPlayerMappableKeySlot::First;
	playerKeyArgs.NewKey = inputChord.Key;

	inputUserSettings->MapPlayerKey(playerKeyArgs, tagContainer);
	inputUserSettings->ApplySettings();
	inputUserSettings->SaveSettings();

	UEventBus::OnUpdateKeyInfo.Broadcast();
}
//-----------------------------------------------------------------------------------------------------------