#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMasterComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EStateName : uint8
{
	Health,
	HealthMax,
	HealthRegen,
	Stamina,
	StaminaMax,
	StaminaRegen
};
//-----------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UStateMasterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateMasterComponent();

protected:
	virtual void BeginPlay() override;
	
};
//-----------------------------------------------------------------------------------------------------------