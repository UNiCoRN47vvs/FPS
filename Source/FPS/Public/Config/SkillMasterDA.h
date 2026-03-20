#pragma once

#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "Enums/ElementsType.h"
#include "SkillMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USkillMasterDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") float AttackDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") FName SkillSocketBoneName = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") EElementsType SkillElement1 = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") UAnimMontage* AttackMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") UNiagaraSystem* SkillMontageEffect = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") UNiagaraSystem* SkillProjectileEffect = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") TArray<UNiagaraSystem*> SkillEffect = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_DA") TArray<FLinearColor> SkillEffectColor = {};
};
//-----------------------------------------------------------------------------------------------------------