#pragma once

#include "ActorComponents/Skill/SkillMasterComponent.h"
#include "PlayerSC.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USkillScrollDA;
class USkeletalMeshComponent;
class UCameraComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UPlayerSC : public USkillMasterComponent
{
	GENERATED_BODY()

public:	
	UPlayerSC();
	void InitSkillComponent(USkeletalMeshComponent* skeletalMeshComponent, UCameraComponent* cameraComponent);
	void SetCurrentSkill(USkillScrollDA* scrollDA);
	//**************************
	//Skills
	void UseMagicBall();
	void UseLightningWall();
	void UseIceGroundAttack();
	//**************************

protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY() USkillScrollDA* ScrollDA;
	UPROPERTY() USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY() UCameraComponent* PlayerCameraComponent;

private:
	FActorSpawnParameters SpawnParams;
};
//-----------------------------------------------------------------------------------------------------------