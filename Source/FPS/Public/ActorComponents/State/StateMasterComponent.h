#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/StateName.h"
#include "Enums/ElementsType.h"
#include "StateMasterComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
#pragma region Forward Region
class UTexture2D;
class USkillMasterDA;
class USkillDefenseDA;
class UFPSGameInstance;
class ACharacterMaster;
class UNiagaraSystem;
class UNiagaraComponent;
class UStatObjectMaster;
struct FDamageStruct;
struct FPortalStat;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FElementsChanse : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C") EElementsType ElementType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C", meta = (ToolTip = "Deactivate Effect Time in seconds")) int32 DeactivateEffectTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C", meta = (ToolTip = "Maximum Stack for Effect")) int32 MaxStackPullEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C", meta = (ToolTip = "Percent per Stack Effect ")) float StackEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C", meta = (ToolTip = "Elemental Percent Damage min")) float ElementalPDMin;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C", meta = (ToolTip = "Elemental Percent Damage max")) float ElementalPDMax;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C") UTexture2D* ElementIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "E_C") UNiagaraSystem* ElementNiagara;
};
//-----------------------------------------------------------------------------------------------------------
#pragma region Buff Debuff Structs
struct FBuffDebuffMasterData
{
	uint8 bIsEffect : 1;
	float CurrentTickTime = 0.0;
	float CurrentLifeTime = 0.0;
	UPROPERTY() UNiagaraComponent* NiagaraComponent;
};
//**************************
struct FFireEffectData : public FBuffDebuffMasterData
{
	float Damage = 0.0;
	FElementsChanse FireData = {};
};
//**************************
struct FBuffDebuffStackData : public FBuffDebuffMasterData
{
	int32 CurrentStackPullEffect = 0;
};
struct FPoisonEffectData : public FBuffDebuffStackData
{
	float Damage = 0.0;
};
//**************************
struct FDilationUpBuff : public FBuffDebuffMasterData
{
	float DilationValueBuff = 0.0;
};
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UStateMasterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateMasterComponent();
	//**************************
	void InitStateComponent(const FPortalStat& PortalStat);
	void InitSpecificStat();
	//**************************
	//Getters
	TMap<EStateName, float>& GetStateMap();
	float GetStateMapElem(EStateName stateName);
	//**************************
	float FindElementChanseFromElement(EElementsType elementType);
	void RestoreAfterDeath();
	void ApplyHeal(float HealPoint);
	void ApplyDamage(FDamageStruct& damageStruct);
	virtual void AuraEffect(USkillDefenseDA* SkillDA);
	void ApplySandStorm(USkillMasterDA* SkillDA, float EnemyDamage);
	//**************************
	void ApplyDilationUpBuff(float dilationValueBuff, float dilationTime);

	TDelegate<void(bool, int32, UTexture2D*)> OnFireEffect;
	TDelegate<void(bool, UTexture2D*)> OnPhysicalEffect;
	TDelegate<void(bool, int32, UTexture2D*)> OnColdEffect;
	TDelegate<void(bool, int32, UTexture2D*)> OnPoisonEffect;
	TMulticastDelegate<void(EStateName, float, float)> OnChangeState;
	TMulticastDelegate<void(FDamageStruct&)> OnDealDamage;
	TMulticastDelegate<void(FDamageStruct&)> OnTakeDamage;

	uint8 bIsDead : 1;
protected:
	virtual void BeginPlay() override;
	void BuffDebuff();
	float DamageResistance(float damage, EElementsType firstElement);
	void ApplyElementEffect(const FDamageStruct& damageStruct);

	void ApplyPhysicalEffect(FElementsChanse* elementsChanseStruct);
	void PhysicalTimerFunc();
	void ApplyFireEffect(float damage, FElementsChanse* elementsChanseStruct);
	void FireTimerFunc();
	void ApplyColdEffect(FElementsChanse* elementsChanseStruct);
	void ColdTimerFunc();
	void ApplyPoisonEffect(float damage, FElementsChanse* elementsChanseStruct);
	void PoisonTimerFunc();
	void ApplyLightningEffect(float damage, FElementsChanse* elementsChanseStruct);
	void DilationUpBuffFunc();

	FElementsChanse* GetElementsData(EElementsType ElementType);
	float GetStateResistance(EElementsType ElementType);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "H_S_C") TMap<EStateName, float> StateMap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "H_S_C") UDataTable* ElementsDataTable;

#pragma region Buffs Debuffs
	//**************************
	float BuffDebuffTimerTime;
	UPROPERTY() FTimerHandle BuffDebuffTimerHandle;

	//Physical
	FBuffDebuffStackData PhysicalEffect;
	//Fire
	TArray<FFireEffectData> FireEffectArray;
	//Cold
	FBuffDebuffStackData ColdEffect;
	//Poison
	FPoisonEffectData PoisonEffect;
	//Lightning
	FBuffDebuffMasterData LightningEffect;
	//Speed Buff
	FDilationUpBuff DilationUpBuff;
	//Sand Debuff
	FPoisonEffectData SandDebuff;
	//**************************
#pragma endregion

	UPROPERTY() TMap<EStateName, UStatObjectMaster*> StatObjects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M_C") FGameplayTag AttackTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M_C") FGameplayTag DeffenceTag;
private:
	void ApplyElementalNiagara(FBuffDebuffMasterData& elementStruct, FElementsChanse* elementsChanseStruct);
	void SandDebuffTimer(FDamageStruct& DamageStruct);
	void IncreaseStateElem(EStateName stateName, float value);
	bool HasTimeEmplace(FBuffDebuffMasterData& structData, float interval);
	virtual void DeathTimerClear();
	UFUNCTION() void DestroyNiagaraAfter(UNiagaraComponent* pSystem);
	UPROPERTY() ACharacterMaster* CharacterOwner;
};
//-----------------------------------------------------------------------------------------------------------