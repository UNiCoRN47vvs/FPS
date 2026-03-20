#pragma once

#include "SkillActors/SkillActor.h"
#include "WaveSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AWaveSA : public ASkillActor
{
	GENERATED_BODY()
public:
	AWaveSA();
	virtual void InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Project Circle Wave") USceneComponent* DefaultSceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Project Circle Wave") UStaticMeshComponent* StaticMesh;
protected:
	virtual void BeginPlay() override;
	UFUNCTION() void StaticMeshComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
//-----------------------------------------------------------------------------------------------------------