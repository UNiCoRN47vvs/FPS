#pragma once

#include "character/CharacterMaster.h"
#include "Logging/LogMacros.h"
#include "Config/CharacterMasterDA.h"
#include "ActorComponents/StorageComponent.h"
#include "Enums/StateName.h"
#include "FPSCharacter.generated.h"
//-----------------------------------------------------------------------------------------------------------
#pragma region Forward Declaration
class UInputAction;
class USphereComponent;
class AFPSPlayerController;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UPlayerStateComponent;
class UHealthStaminaComponent;
class UInteractComponent;
class UInventoryComponent;
class UStorageWidget;
class UEquipmentComponent;
class UMasterSave;
class UEnhancedInputComponent;
class UFPSGameInstance;
class UPlayerQuestComponent;
class UPlayerSC;
class UEnemyMasterMasterDA;
class UEventBus;
class USkillScrollDA;
class UCraftComponent;
struct FInputActionValue;
struct FInputActionInstance;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
UCLASS(config=Game)
class AFPSCharacter : public ACharacterMaster
{
	GENERATED_BODY()

public:
	AFPSCharacter();
	//**************************
	//Interfaces
	virtual void ApplyDeath();
	//**************************
	virtual USkeletalMeshComponent* GetCharacterMesh() override;
	virtual void DealDamage(FDamageStruct& damageStruct, FHitResult hitResult = {}) override;
	virtual void HitReaction() override;
	virtual void ApplyInteract(EStorageType storageType, UStorageComponent* storageComponent = nullptr) override;
	virtual bool PickUpItem(int32& ItemCount, UItemMasterDA* ItemDA) override;
	UFUNCTION(BlueprintCallable) void TESTING_PickUpItem(int32 itemCount, UItemMasterDA* itemDA, int32 itemLevel, FStatValueStruct statValue);
	virtual void TriggerQuestInteract(UQuestInteractTargetMasterDA* questInteractDA) override;
	void PickUpCurrency(const FCurrency& currencyStruct);
	//**************************
	//Getters
	UInputAction* GetControlMapIA(const FName& name);
	USkeletalMeshComponent* GetMesh1P() const;
	UCameraComponent* GetFirstPersonCameraComponent() const;
	virtual UInteractComponent* GetInteractComponent() override;
	UCameraComponent* GetCameraComponent();
	virtual UInventoryComponent* GetInventoryComponent() override;
	UEquipmentComponent* GetEquipmentComponent();
	UPlayerStateComponent* GetPlayerStateComponent();
	UPlayerQuestComponent* GetQuestComponent();
	UPlayerSC* GetSkillComponent();
	//**************************
	UFUNCTION(BlueprintCallable, Category = "Save Game") void SaveGame();

	void ActivateCraftSystem();
	bool DoesHasEmptySlots(int32  numberEmptySlots);
	template <bool bIsStart> void Sprint();
	void RestoreAfterDeath();

	uint8 bIsReload : 1;
	uint8 bStopMoving : 1;
	uint8 bStopFastSelector : 1;
	float StandartSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float SpeedPercent;

	TDelegate<void()> OnShowHideInventoryWidget;
	TDelegate<void()> OnShowHideEscapeMenuWidget;
	TDelegate<void()> OnShowHideQuestMenuWidget;
	TDelegate<void(bool)> OnMove;
	TDelegate<void(int32)> OnEquipWeapon;
	TDelegate<void(int32)> OnActivateAudus;
	TMulticastDelegate<void(bool)> OnChangeSprint;

protected:
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Move(const FInputActionValue& value);
	void StopMove(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void LoadGame();
	//**************************
	//Interfaces
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	//**************************

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh) USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) TMap<FName, UInputAction*> ControlMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Character") UMetaSoundSource* FootstepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Character") TSubclassOf<UCraftComponent> CraftComponentClass;


	float FootstepSpeed;
	float FootstepTimeCount;
private:
	void SetLoadData(TArray<FStorageTab>& storage, UStorageComponent* storageComponent);
	void Interact();
	void ShowHideInventoryWidget();
	void ShowHideEscapeMenuWidget();
	void ShowHideQuestMenu();
	void UseSelectedPotion();
	void UseSelectedSkill();
	void UseFastPickUp();
	void PlaySkillAnimation(USkillScrollDA* scrollDA);
	template <bool bIsShow> void ShowHideFastSelector(const FInputActionInstance& ActionData);

	template <int32 weaponIndex> void EquipWeapon();
	template <int32 audusIndex> void ActivateAudus();
	UFUNCTION() void FireTriggered(const FInputActionInstance& ActionData);
	
	UPROPERTY() UInteractComponent* InteractComponent;
	UPROPERTY() UInventoryComponent* InventoryComponent;
	UPROPERTY() UEquipmentComponent* EquipmentComponent;
	UPROPERTY() UPlayerStateComponent* PlayerStateComponent;
	UPROPERTY() UPlayerQuestComponent* QuestComponent;
	UPROPERTY() UPlayerSC* SkillComponent;
	UPROPERTY() UCraftComponent* CraftComponent;
	UPROPERTY() AFPSPlayerController* PlayerController;
	UPROPERTY() UFPSGameInstance* GameInstance;
	UPROPERTY() UEnhancedInputComponent* EnhancedInputComponent;
};
//-----------------------------------------------------------------------------------------------------------
