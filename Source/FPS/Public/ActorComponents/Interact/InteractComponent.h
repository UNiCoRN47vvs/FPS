#pragma once

#include "FPS/FPS.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UCameraComponent;
class UInfoInteractWidget;
class IItemInteract;
class IItemInfo;
class IInteractInfo;
class UEventBus;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

	void WidgetInfo(bool bCreate, IInteractInfo* itemInfo);
	const TWeakObjectPtr<AActor>& GetTargetActor();

protected:
	virtual void BeginPlay() override;
private:
	void LineTraceCall(); //При наведении создаем/удаляем инфовиджет
	void OnAcyncTraceDelegate(const FTraceHandle& traceHandle, FTraceDatum& traceDatum);
	FString StringName;
	UPROPERTY() UCameraComponent* CameraComponent; 
	UPROPERTY() FTimerHandle LineTraceTimer;
	UPROPERTY() TWeakObjectPtr<AActor> TargetActor;
	FTraceDelegate OnTraceDelegate;
		
};
//-----------------------------------------------------------------------------------------------------------