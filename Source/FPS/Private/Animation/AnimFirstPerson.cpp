#include "Animation/AnimFirstPerson.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "Items/Weapons/WeaponMaster.h"
//-----------------------------------------------------------------------------------------------------------
void UAnimFirstPerson::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}
//-----------------------------------------------------------------------------------------------------------
void UAnimFirstPerson::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	USkeletalMeshComponent* skeletalMesh = nullptr;
	float footstepSpeed = 0.0;
	if (!IsValid(PlayerCharacter) || !MovementComponent)
	{
		APawn* pawn = TryGetPawnOwner();
		if (!pawn)
		{
			//UE_LOG(LogTemp, Warning, TEXT("-[%S]- : LocalPawn = nullptr"), __FUNCTION__);
			return;
		}
		PlayerCharacter = Cast<AFPSCharacter>(pawn);
		CHECK_PTR(PlayerCharacter)

		MovementComponent = PlayerCharacter->GetMovementComponent();
	}

	bIsInAir = MovementComponent->IsFalling();
}
//-----------------------------------------------------------------------------------------------------------
void UAnimFirstPerson::InitAnimInstance(UEquipmentComponent* ActorComponent)
{
	CHECK_PTR(ActorComponent)

	if (!PlayerCharacter)
	{
		APawn* pawn = TryGetPawnOwner();
		CHECK_PTR(pawn)
		PlayerCharacter = Cast<AFPSCharacter>(pawn);
		CHECK_PTR(PlayerCharacter)
	}

	ActorComponent->RifleStateDelegate.BindUObject(this, &UAnimFirstPerson::ChangeRifleState);
	PlayerCharacter->OnMove.BindUObject(this, &UAnimFirstPerson::Move);
}
//-----------------------------------------------------------------------------------------------------------
void UAnimFirstPerson::Move(bool IsMove)
{
	IsMoving = IsMove;
}
//-----------------------------------------------------------------------------------------------------------
void UAnimFirstPerson::ChangeRifleState(const bool bIsActive, EItemType WeaponType)
{
	switch (WeaponType)
	{
	case EItemType::MagicWeapon:
		bHasMagicWeapon = bIsActive;
		break;
	case EItemType::All:
	case EItemType::Supplies:
	case EItemType::Armor:
	case EItemType::Magazine:
	case EItemType::MagicMagazine:
	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------

