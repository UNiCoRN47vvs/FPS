#include "MainMenu/MainMenuController.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "FirstPerson/FPSGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/MainMenu/MainMenuWidget.h"
//-----------------------------------------------------------------------------------------------------------
void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	CreateLoadScreen();

	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), WBPMainMenu);
	CHECK_PTR(MainMenuWidget)
	MainMenuWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, MainMenuWidget, EMouseLockMode::DoNotLock, false);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (subsystem && UFPSGameInstance::OnGetInputMapingContext.IsBound())
		subsystem->GetUserSettings()->RegisterInputMappingContext(UFPSGameInstance::OnGetInputMapingContext.Execute());
	
}
//-----------------------------------------------------------------------------------------------------------
void AMainMenuController::CreateLoadScreen()
{
	LoadScreenWidget = CreateWidget<UUserWidget>(GetWorld(), WBPLoadScreen);
	CHECK_PTR(LoadScreenWidget)
	LoadScreenWidget->AddToViewport();
}