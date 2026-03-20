#pragma once

#include "FPS/FPS.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Skill/PlayerSC.h"
#include "PlayerAnimNotifyMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPlayerAnimNotifyMaster : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	bool PlayerCharacterIsValid(USkeletalMeshComponent* MeshComponent);
	AFPSCharacter* PlayerCharacter;
};
//-----------------------------------------------------------------------------------------------------------