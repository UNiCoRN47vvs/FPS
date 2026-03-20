#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerAttackNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPlayerAttackNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;
};
//-----------------------------------------------------------------------------------------------------------