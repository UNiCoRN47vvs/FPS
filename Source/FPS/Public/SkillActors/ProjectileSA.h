#pragma once

#include "SkillActors/SkillActor.h"
#include "ProjectileSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USphereComponent;
class UNiagaraSystem;
class UProjectileMovementComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AProjectileSA : public ASkillActor
{
	GENERATED_BODY()

public:
	AProjectileSA();

	virtual void InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA) override;
	virtual void InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner) override;
	void ApplyNiagaraParameters(UNiagaraSystem* niagaraSystem, const FVector& niagaraSize);

	void MakeProjectileHoming(USceneComponent* sceneComponent);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "M_B_PS") USphereComponent* CollisionSphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "M_B_PS") UProjectileMovementComponent* ProjectileComponent;

protected:
	virtual void BeginPlay() override;
	UFUNCTION() virtual void SphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	
	UPROPERTY() USkillScrollDA* ScrollDA;
	UPROPERTY() USkillAttackDA* SkillAttackDA;
	float ElementChance;
};
//-----------------------------------------------------------------------------------------------------------