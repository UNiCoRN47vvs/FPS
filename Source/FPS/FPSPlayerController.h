#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/DragDropInterface.h"
#include "FPSPlayerController.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInputMappingContext;
class UMainHUDWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AFPSPlayerController : public APlayerController, public IDragDropInterface
{
	GENERATED_BODY()

public:
	virtual void DragDropOperation(UInventoryComponent* StorageComponent, int Index, bool bIsDrop);
	UMainHUDWidget* MainHUD;
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext* InputMappingContext;
private:
	UPROPERTY(EditDefaultsOnly, Category = "FPS Player Controller") TSubclassOf<UMainHUDWidget> MainHUDWidget;

};
//-----------------------------------------------------------------------------------------------------------