#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "HealthStaminaComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChangeState, EStateName, StateName, double, CurrentValue, double, MaxValue);
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UHealthStaminaComponent : public UStateMasterComponent
{
	GENERATED_BODY()

public:	
	
	UHealthStaminaComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void ChangeStateValue(EStateName StateName, double Value, bool bIncrease);
	double GetStateMapElem(EStateName StateName);

	UPROPERTY(BlueprintAssignable, Category = "Health Stamina Component")
	FChangeState OnChangeState;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Stamina Component")
	TMap<EStateName, double> StateMap;

private:
	void RegenHealth();
	void RegenStamina();
	UFUNCTION()
	void RegenTimerManager(EStateName StateName, double CurrentValue, double MaxValue);
	UFUNCTION()
	void WasteStaminaTimerManager(bool bStart);
	void WasteStamina();

	bool bStaminaTimerBlock;
	FTimerHandle HealthTimerHandle;
	FTimerHandle StaminaTimerHandle;
	FTimerHandle WasteStaminaTimerHandle;
	AFPSCharacter* PlayerCharacter;
};
//-----------------------------------------------------------------------------------------------------------