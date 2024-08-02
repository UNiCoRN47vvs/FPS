#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/PlayerInteract.h"
#include "FPSCharacter.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UHealthStaminaComponent;
class UInteractComponent;
struct FInputActionValue;
//-----------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeSprint, bool, bStart);
//-----------------------------------------------------------------------------------------------------------
UCLASS(config=Game)
class AFPSCharacter : public ACharacter, public  IPlayerInteract
{
	GENERATED_BODY()

public:
	AFPSCharacter();
	virtual void InteractPlayerWithItem(bool bTurnOn) override;
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	UHealthStaminaComponent* GetHealthStaminaComponent();
	UInteractComponent* GetInteractComponent();
	UCameraComponent* GetCameraComponent();
	void StopSprint();

	UPROPERTY(BlueprintAssignable, Category = "Health Stamina Component")
	FChangeSprint OnChangeSprint;

protected:
	virtual void BeginPlay();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
private:
	void Sprint();

	double StandartSpeed;
	UCharacterMovementComponent* CharacterMovement;
	UHealthStaminaComponent* HealthStaminaComponent;
	UInteractComponent* InteractComponent;

};
//-----------------------------------------------------------------------------------------------------------