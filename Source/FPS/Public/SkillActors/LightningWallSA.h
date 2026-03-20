#pragma once

#include "SkillActors/ProjectileSA.h"
#include "LightningWallSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UBoxComponent;
class ACharacterMaster;
class UNiagaraSystem;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ALightningWallSA : public AProjectileSA
{
	GENERATED_BODY()
public:
	ALightningWallSA();

protected:
	virtual void BeginPlay() override;
	virtual void SphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "L_W_PS") UBoxComponent* BoxComponent;

	virtual void InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner) override;
	void SkillDealDamage();
	UFUNCTION() void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle DamageTimer;
	UPROPERTY() TArray<ACharacterMaster*> Characters;

protected:

};
//-----------------------------------------------------------------------------------------------------------