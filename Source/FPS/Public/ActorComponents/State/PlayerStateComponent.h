#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Struct/StatValueStruct.h"
#include "PlayerStateComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSPlayerController;
class AFPSCharacter;
class AEnemyMaster;
class USkillDefenseDA;
class UNiagaraComponent;
class UInventoryComponent;
//-----------------------------------------------------------------------------------------------------------
struct FIceCage
{
	uint8 bIsExist : 1 = false;
	float Time = 0.0f;
	float SpeedPercent = 0.0f;
	UPROPERTY() UNiagaraComponent* NiagaraComponent = nullptr;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UPlayerStateComponent : public UStateMasterComponent
{
	GENERATED_BODY()

public:	
	UPlayerStateComponent();

	UFUNCTION(BlueprintCallable) void ChangeStateValue(EStateName stateName, float value, bool bIncrease);
	virtual void AuraEffect(USkillDefenseDA* SkillDA) override;
	void UseConsumableSupplies(const TMap<EStateName, float>& stats);
	void SetEquipStat(const FStatValueStruct& armorStat);
	bool WasteMana(float manaCost, bool bIsWasteMana);

	static TDelegate<void(APawn*, USkillDefenseDA*)> OnApplyIceCage;
	uint8 bIsSprinting : 1;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void WasteStamina();
	void WeightCalculation();
	void ApplyIceCage(APawn* target, USkillDefenseDA* skillDA);
	void RemoveIceCage();
	UFUNCTION()	void RegenTimerManager(EStateName stateName, float currentValue, float maxValue);
	UFUNCTION()	void WasteStaminaTimerManager(bool bStart);

	uint8 bStaminaTimerBlock : 1;
	UPROPERTY() FTimerHandle HealthTimerHandle;
	UPROPERTY() FTimerHandle StaminaTimerHandle;
	UPROPERTY() FTimerHandle ManaTimerHandle;
	UPROPERTY() FTimerHandle WasteStaminaTimerHandle;
	UPROPERTY() FTimerHandle IceCageTimerHandle;
	UPROPERTY() AFPSPlayerController* PlayerController;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() UInventoryComponent* InventoryComponent;
	FIceCage IceCageStruct;
	TMap<EStateName, float> StandartStateMap;
};
//-----------------------------------------------------------------------------------------------------------