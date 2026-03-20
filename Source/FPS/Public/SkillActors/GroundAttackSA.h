#pragma once

#include "SkillActors/SkillActor.h"
#include "GroundAttackSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UBoxComponent;
class USkillScrollDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AGroundAttackSA : public ASkillActor
{
	GENERATED_BODY()
public:
	AGroundAttackSA();

	virtual void InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_A_SA") UBoxComponent* BoxComponent;
protected:
	UFUNCTION() void BeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_A_SA") float LengthSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G_A_SA") float WidthSize;
	UPROPERTY() USkillScrollDA* ScrollDA;
	UPROPERTY() UWorld* World;
	UPROPERTY() TArray<AActor*> CharacterArray;

private:
	void ApplyTimerSize(float value);
};
//-----------------------------------------------------------------------------------------------------------