#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UCameraComponent;
class AFPSCharacter;
class UInfoInteractWidget;
class IItemInteract;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

	void SetInteractLine(bool bTurnOn);
	AActor* GetTargetActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	int TimerCounter;
private:
	void LineTraceCall();
	//При наведении создаем/удаляем инфовиджет
	void WidgetInfo(bool bCreate, IItemInteract* ItemInteract);

	AFPSCharacter* PlayerCharacter;
	UCameraComponent* CameraComponent;
	FTimerHandle LineTraceTimer;
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, Category = "Interact Component")
	TSubclassOf<UInfoInteractWidget> BPInteractWidget;

	UInfoInteractWidget* InteractWidget;
		
};
//-----------------------------------------------------------------------------------------------------------