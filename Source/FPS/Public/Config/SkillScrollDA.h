
#pragma once

#include "CoreMinimal.h"
#include "Config/ItemMasterDA.h"
#include "Enums/ElementsType.h"
#include "Struct/StatRange.h"
#include "SkillScrollDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class ASkillActor;
class UNiagaraSystem;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USkillScrollDA : public UItemMasterDA
{
	GENERATED_BODY()
public:
	virtual TMap<FString, FText> GetItemInfo() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") FName SkillSocketBoneName = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") EElementsType SkillElement1 = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") UAnimMontage* AttackMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") USoundWave* StartSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") USoundWave* EndSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") TSoftObjectPtr<UNiagaraSystem> ProjectileNiagara = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") TSoftObjectPtr<UNiagaraSystem> ExplodeNiagara = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") float ManaCost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") FStatRange SkillAttackDamage = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") FLinearColor SkillColor = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C_DA") TSubclassOf<ASkillActor> AttackProjectile = nullptr;
};
//-----------------------------------------------------------------------------------------------------------