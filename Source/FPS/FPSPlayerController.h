#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInputMappingContext;
class UMainHUDWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UMainHUDWidget* MainHUD;
	
protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext* InputMappingContext;
private:
	UPROPERTY(EditDefaultsOnly, Category = "FPS Player Controller") TSubclassOf<UMainHUDWidget> MainHUDWidget;

};
//-----------------------------------------------------------------------------------------------------------