#include "Animation/Enemies/EnemyMasterAnimInstance.h"

//-----------------------------------------------------------------------------------------------------------
void UEnemyMasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!EnemyPawn)
	{
		EnemyPawn = TryGetPawnOwner();
		if (!EnemyPawn)
			return;
	}

	Speed = EnemyPawn->GetVelocity().Size();
}
