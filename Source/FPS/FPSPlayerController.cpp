#include "FPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	MainHUD = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidget);
	if (MainHUD)
		MainHUD->AddToViewport();

}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::DragDropOperation(UInventoryComponent* StorageComponent, int Index, bool bIsDrop)
{
}