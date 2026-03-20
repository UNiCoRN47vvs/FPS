#pragma once

#include "SkillActors/SpecializedSA.h"
#include "MultiSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UEnemyMasterDA;
class AEnemyMaster;
class USkillMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AMultiSA : public ASpecializedSA
{
	GENERATED_BODY()

public:
	AMultiSA();
	
	virtual void ActivateSkill() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_A_M") TArray<USkillMasterDA*> SkillsDA;

	int32 SkillIndex;
	FVector PlayerLocation;
private:
	UFUNCTION() void MultiStep2(UNiagaraComponent* finishedComponent);
};
//-----------------------------------------------------------------------------------------------------------