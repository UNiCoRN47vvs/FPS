#pragma once

#include "FPS/FPS.h"
#include "Animation/AnimInstance.h"
#include "EnemyMasterAnimInstance.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemyMasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "E_M_A_I") float Speed;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "E_M_A_I") APawn* EnemyPawn;
	
private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
//-----------------------------------------------------------------------------------------------------------