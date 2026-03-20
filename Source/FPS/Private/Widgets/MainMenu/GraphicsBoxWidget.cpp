#include "Widgets/MainMenu/GraphicsBoxWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ComboBoxString.h"
//-----------------------------------------------------------------------------------------------------------
void UGraphicsBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FIntPoint> resolutions = {};
	UGameUserSettings* userSettings = UGameUserSettings::GetGameUserSettings();

	CHECK_PTR(userSettings)

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(resolutions);

	for (FIntPoint& item : resolutions)
	{
		ResolutionCB->AddOption(FString::FromInt(item.X) + FString(" x ") + FString::FromInt(item.Y));
	}

	FullscreenModeCB->AddOption(FString(TEXT("Fullscreen")));
	FullscreenModeCB->AddOption(FString(TEXT("Fullscreen Windowed")));
	FullscreenModeCB->AddOption(FString(TEXT("Windowed")));

	FullscreenModeCB->OnSelectionChanged.AddDynamic(this, &UGraphicsBoxWidget::OnFullscreenModeChanged);
	ResolutionCB->OnSelectionChanged.AddDynamic(this, &UGraphicsBoxWidget::OnResolutionChanged);

	ResolutionCB->SetSelectedOption(FString::FromInt(userSettings->GetScreenResolution().X) + FString(" x ") + FString::FromInt(userSettings->GetScreenResolution().Y));
	FullscreenModeCB->SetSelectedOption(FString::Printf(TEXT("%d"), userSettings->GetFullscreenMode()));
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsBoxWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::Direct)
		return;

	TArray<FString> tokens = {};
	FIntPoint resolution = {};
	UGameUserSettings* userSettings = UGameUserSettings::GetGameUserSettings();

	CHECK_PTR(userSettings)

	SelectedItem.ParseIntoArray(tokens, TEXT(" x "), true);

	if (!tokens.IsValidIndex(0) || !tokens.IsValidIndex(1))
		return;

	resolution.X = FCString::Atoi(*tokens[0]);
	resolution.Y = FCString::Atoi(*tokens[1]);

	userSettings->SetScreenResolution(resolution);
	userSettings->ApplyResolutionSettings(true);
}
//-----------------------------------------------------------------------------------------------------------
void UGraphicsBoxWidget::OnFullscreenModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::Direct)
		return;

	UGameUserSettings* userSettings = UGameUserSettings::GetGameUserSettings();

	CHECK_PTR(userSettings)

	if (SelectedItem == FString(TEXT("Fullscreen")))
		userSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	else if(SelectedItem == FString(TEXT("Fullscreen Windowed")))
		userSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	else if(SelectedItem == FString(TEXT("Windowed")))
		userSettings->SetFullscreenMode(EWindowMode::Windowed);

	FullscreenModeCB->SetSelectedOption(FString::Printf(TEXT("%d"), userSettings->GetFullscreenMode()));

	userSettings->ApplySettings(true);
}
//-----------------------------------------------------------------------------------------------------------
