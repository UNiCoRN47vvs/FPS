
#pragma once

#include "CoreMinimal.h"
#include "AnimNotify/PlayerAnimNotify/PlayerAnimNotifyMaster.h"
#include "LightningWallNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ULightningWallNotify : public UPlayerAnimNotifyMaster
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------