#pragma once

#include "SkillActors/ProjectileSA.h"
#include "MagicBallSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AMagicBallSA : public AProjectileSA
{
	GENERATED_BODY()
public:
	virtual void InitParam(USkillScrollDA* scrollDA, float elementChance, AActor* owner) override;

protected:
	virtual void SphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) override;

	void ApplyMagicBallDamage();
};
//-----------------------------------------------------------------------------------------------------------