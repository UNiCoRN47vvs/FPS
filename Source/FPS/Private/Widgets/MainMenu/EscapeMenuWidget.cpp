#include "Widgets/MainMenu/EscapeMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "FPS/FPSPlayerController.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Widgets/MainMenu/MainMenuWidget.h"
#include "Widgets/MainMenu/SignboardWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UEscapeMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UEscapeMenuWidget::ApplyResumeButton);
	ExitSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UEscapeMenuWidget::ApplyExitButton);

	SettingsSignboard->NewGameSignboard->RemoveFromParent();
	SettingsSignboard->LoadGameSignboard->RemoveFromParent();
	SettingsSignboard->ExitSignboard->RemoveFromParent();

	SettingsSignboard->SettingsSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UEscapeMenuWidget::ShowHideSignboard);
	SettingsSignboard->SettingsBackSignboard->ButtonSignboard->OnClicked.AddDynamic(this, &UEscapeMenuWidget::ShowHideSignboard);
}
//-----------------------------------------------------------------------------------------------------------
void UEscapeMenuWidget::ApplyResumeButton()
{
	AFPSPlayerController* playerController = GetOwningPlayer<AFPSPlayerController>();

	CHECK_PTR(playerController)
	CHECK_PTR(playerController->MainHUD)

	playerController->MainHUD->CreateRemoveEscapeMenu(false);
}
//-----------------------------------------------------------------------------------------------------------
void UEscapeMenuWidget::ApplyExitButton()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
//-----------------------------------------------------------------------------------------------------------
void UEscapeMenuWidget::ShowHideSignboard()
{
	if (ResumeSignboard->GetVisibility() == ESlateVisibility::Collapsed)
	{
		ResumeSignboard->SetVisibility(ESlateVisibility::Visible);
		ExitSignboard->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ResumeSignboard->SetVisibility(ESlateVisibility::Collapsed);
		ExitSignboard->SetVisibility(ESlateVisibility::Collapsed);
	}
}
//-----------------------------------------------------------------------------------------------------------