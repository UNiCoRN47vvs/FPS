#pragma once

#include "FPS/FPS.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UMainMenuWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
public:
	void CreateLoadScreen();
	UPROPERTY() UMainMenuWidget* MainMenuWidget;
	UPROPERTY() UUserWidget* LoadScreenWidget;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Menu Controller") TSubclassOf<UUserWidget> WBPMainMenu;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Menu Controller") TSubclassOf<UUserWidget> WBPLoadScreen;
};
//-----------------------------------------------------------------------------------------------------------