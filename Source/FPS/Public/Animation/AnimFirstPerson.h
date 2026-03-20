#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MetasoundSource.h"
#include "AnimFirstPerson.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
class UEquipmentComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UAnimFirstPerson : public UAnimInstance
{
	GENERATED_BODY()
public:
	void InitAnimInstance(UEquipmentComponent* ActorComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A_F_P") bool bHasMagicWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A_F_P") bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A_F_P") bool IsMoving;
	
protected:
	virtual void NativeInitializeAnimation() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "A_F_P") AFPSCharacter* PlayerCharacter;
	UPROPERTY() UPawnMovementComponent* MovementComponent;
private:
	void Move(bool IsMove);
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UFUNCTION() void ChangeRifleState(const bool bIsActive, EItemType WeaponType);
};
//-----------------------------------------------------------------------------------------------------------