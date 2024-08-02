#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UCameraComponent;
class AFPSCharacter;
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

private:
	void LineTraceCall();

	int TimerCounter;
	AFPSCharacter* PlayerCharacter;
	UCameraComponent* CameraComponent;
	FTimerHandle LineTraceTimer;
	AActor* TargetActor;

		
};
//-----------------------------------------------------------------------------------------------------------