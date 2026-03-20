#pragma once

#include "SkillActors/SpecializedSA.h"
#include "ZoneSA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UBoxComponent;
class ACharacterMaster;
class UEnemyMasterDA;
class AEnemyMaster;
class USkillMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AZoneSA : public ASpecializedSA
{
	GENERATED_BODY()

public:
	AZoneSA();
	
	virtual void ActivateSkill() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "S_B") UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_B") float ZoneLifeTime;
protected:
	virtual void BeginPlay() override;
	UFUNCTION() void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	FTimerHandle ZoneTimer;
	UPROPERTY() ACharacterMaster* PlayerCharacter;
	void ApplyZoneDamage();
};
//-----------------------------------------------------------------------------------------------------------