#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "FirstPerson/FPSGameInstance.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "InputActionValue.h"
#include "ActorComponents/Interact/InteractComponent.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Chest/ChestComponent.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "ActorComponents/State/PlayerStateComponent.h"
#include "ActorComponents/Quest/PlayerQuestComponent.h"
#include "ActorComponents/Skill/PlayerSC.h"
#include "ActorComponents/Craft/CraftComponent.h"
#include "Save/MasterSave.h"
#include "Interfaces/ItemInteract.h"
#include "Struct/DamageStruct.h"
#include "Config/SkillScrollDA.h"
//-----------------------------------------------------------------------------------------------------------
AFPSCharacter::AFPSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));

	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	bIsReload = false;
	bStopMoving = false;
	bStopFastSelector = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	FootstepSpeed = 0.43f;
	SpeedPercent = 100.0f;
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle timerHandle = {};
	FTimerHandle loadScreenTimer = {};
	
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())

	this->DisableInput(PlayerController);

	CHECK_CAST(GameInstance, UFPSGameInstance, GetGameInstance())

	if (!GameInstance->bIsNewGame)
		LoadGame();
	else
		GetWorld()->GetTimerManager().SetTimer(loadScreenTimer, [this]() {PlayerController->RemoveLoadScreen(true); }, 0.33, false);
	
	if (GetSkillComponent())
		SkillComponent->InitSkillComponent(Mesh1P, GetCameraComponent());

	if(GetCharacterMovement())
		StandartSpeed = GetCharacterMovement()->MaxWalkSpeed;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AFPSCharacter::SaveGame, 15.0f, true);

	UEventBus::OnSaveGame.BindUObject(this, &AFPSCharacter::SaveGame);
	UEventBus::OnPlayerSkill.AddUObject(this, &AFPSCharacter::PlaySkillAnimation);
	UEventBus::OnGetEquipmentComponent.BindUObject(this, &AFPSCharacter::GetEquipmentComponent);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UEventBus::OnSaveGame.Unbind();
	UEventBus::OnPlayerSkill.RemoveAll(this);
	UEventBus::OnGetEquipmentComponent.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
// Save and Load
void AFPSCharacter::SaveGame()
{
	AsyncTask(ENamedThreads::GameThread, [this]() 
		{
			FSaveStruct* saveData = nullptr;
			UMasterSave* masterSave = nullptr;
			TArray<AActor*>actors = {};

			CHECK_CAST(GameInstance, UFPSGameInstance, GetGameInstance())

			if (!UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
				return;

			masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
			CHECK_PTR(masterSave)

			saveData = masterSave->MasterSave.Find(GameInstance->GetSaveName());
			CHECK_PTR(saveData)

			if (CraftComponent)
				saveData->Craft = CraftComponent->GetAllStorageTabs();

			saveData->Chest = GetChestComponent()->GetAllStorageTabs();
			saveData->Currency = GetInventoryComponent()->GetCurrency();
			saveData->Equip = GetEquipmentComponent()->GetAllStorageTabs();
			saveData->Inventory = GetInventoryComponent()->GetAllStorageTabs();
			saveData->StateMap = GetPlayerStateComponent()->GetStateMap();
			saveData->MagicMagazine = GetEquipmentComponent()->GetMagicMagazine();
			saveData->CurrentQuests = GetQuestComponent()->GetCurrentQuests();
			saveData->CompletedQuests = GetQuestComponent()->GetCompletedQuests();

			UEventBus::OnUpgradeSave.ExecuteIfBound(saveData->Upgrade);

			Public_Beta_Character_Block

			UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);

		});
}
void AFPSCharacter::LoadGame()
{
	FSaveStruct* saveData = nullptr;
	UMasterSave* masterSave = nullptr;

	if (!UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
		return;

	CHECK_CAST(GameInstance, UFPSGameInstance, GetGameInstance())

	masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));

	CHECK_PTR(masterSave)

	UEventBus::OnShowFPS.ExecuteIfBound(masterSave->SettingsSave.bIsShowFPS);

	saveData = masterSave->MasterSave.Find(GameInstance->GetSaveName());
	CHECK_PTR(saveData)

	SetLoadData(saveData->Chest, GetChestComponent());
	SetLoadData(saveData->Inventory, GetInventoryComponent());
	SetLoadData(saveData->Equip, GetEquipmentComponent());
	GetInventoryComponent()->SetCurrency(saveData->Currency);
	GetPlayerStateComponent()->GetStateMap() = saveData->StateMap;
	GetQuestComponent()->SetLoadedData(saveData->CurrentQuests, saveData->CompletedQuests);

	GetEquipmentComponent()->InitArmorStat();
	GetEquipmentComponent()->SetMagazines(saveData->MagicMagazine);
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())

	FTimerHandle loadScreenTimer = {};
	FTimerHandle loadSubFuncTimer = {};
	GetWorld()->GetTimerManager().SetTimer(loadScreenTimer, [this]() {PlayerController->RemoveLoadScreen(); }, 0.33, false);

	/*GetWorld()->GetTimerManager().SetTimer(loadSubFuncTimer, [this]()
		{
			FSaveStruct* saveData = nullptr;
			AUpgradeMaster* upgrade = nullptr;
			UMasterSave* masterSave = nullptr;

			FString saveName = {};
			TArray<AActor*> actors = {};

			if (!UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
				return;

			CHECK_CAST(GameInstance, UFPSGameInstance, GetGameInstance())

			masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));

			CHECK_PTR(masterSave)

			if (bIsDebug)
				saveName = DebugSaveName;
			else
				saveName = GameInstance->GetSaveName();

			saveData = masterSave->MasterSave.Find(saveName);
			CHECK_PTR(saveData)

			UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Upgrade")), actors);
			if (!actors.IsEmpty())
			{
				upgrade = Cast<AUpgradeMaster>(actors[0]);
				if (upgrade && upgrade->GetUpgradeComponent())
					SetLoadData(saveData->Upgrade, upgrade->GetUpgradeComponent());
			}

		}, 0.47, false);*/

}
void AFPSCharacter::SetLoadData(TArray<FStorageTab>& storage, UStorageComponent* storageComponent)
{
	CHECK_PTR(storageComponent)

	for (int32 i = 0; i < storage.Num(); ++i)
	{
		if (!storageComponent->GetAllStorageTabs().IsValidIndex(i) || !storage.IsValidIndex(i))
			return;

		for (int32 j = 0; j < storageComponent->GetAllStorageTabs()[i].StorageTab.Num(); ++j)
		{
			if(storage[i].StorageTab.IsValidIndex(j))
				storageComponent->SetItemFromIndex(storage[i].StorageTab[j], i, j);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
//Inputs
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Jump"))), ETriggerEvent::Started, this, &ACharacter::Jump);
		
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Jump"))), ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Move"))), ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Move"))), ETriggerEvent::Completed, this, &AFPSCharacter::StopMove);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Move"))), ETriggerEvent::Canceled, this, &AFPSCharacter::StopMove);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Sprint"))), ETriggerEvent::Started, this, &AFPSCharacter::Sprint<true>);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Sprint"))), ETriggerEvent::Canceled, this, &AFPSCharacter::Sprint<false>);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Sprint"))), ETriggerEvent::Completed, this, &AFPSCharacter::Sprint<false>);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Look"))), ETriggerEvent::Triggered, this, &AFPSCharacter::Look);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Interact"))), ETriggerEvent::Started, this, &AFPSCharacter::Interact);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Inventory"))), ETriggerEvent::Started, this, &AFPSCharacter::ShowHideInventoryWidget);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Escape Menu"))), ETriggerEvent::Started, this, &AFPSCharacter::ShowHideEscapeMenuWidget);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Weapon Equip"))), ETriggerEvent::Started, this, &AFPSCharacter::EquipWeapon<0>);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Audus 1"))), ETriggerEvent::Started, this, &AFPSCharacter::ActivateAudus<3>);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Audus 2"))), ETriggerEvent::Started, this, &AFPSCharacter::ActivateAudus<5>);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Audus 3"))), ETriggerEvent::Started, this, &AFPSCharacter::ActivateAudus<4>);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Shoot"))), ETriggerEvent::Triggered, this, &AFPSCharacter::FireTriggered);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Reload"))), ETriggerEvent::Started, GetEquipmentComponent(), &UEquipmentComponent::ReloadMagazine);
		
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Quest Menu"))), ETriggerEvent::Started, this, &AFPSCharacter::ShowHideQuestMenu);

		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Fast Selector"))), ETriggerEvent::Ongoing, this, &AFPSCharacter::ShowHideFastSelector<true>);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Fast Selector"))), ETriggerEvent::Canceled, this, &AFPSCharacter::ShowHideFastSelector<false>);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Fast Selector"))), ETriggerEvent::Completed, this, &AFPSCharacter::ShowHideFastSelector<false>);
		
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Fast Potion"))), ETriggerEvent::Started, this, &AFPSCharacter::UseSelectedPotion);
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Fast Skill"))), ETriggerEvent::Started, this, &AFPSCharacter::UseSelectedSkill);
		
		EnhancedInputComponent->BindAction(GetControlMapIA(FName(TEXT("Fast Pick Up"))), ETriggerEvent::Started, this, &AFPSCharacter::UseFastPickUp);
	}
	else
		ALARM_LOG
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::Move(const FInputActionValue& value)
{
	float footstepSpeed = 0.0f;
	float speedPercent = SpeedPercent;
	FVector2D movementVector = value.Get<FVector2D>();
	FVector velocity = GetVelocity();
	FVector forwardVector = GetActorForwardVector();

	AddMovementInput(forwardVector, movementVector.Y);
	AddMovementInput(GetActorRightVector(), movementVector.X);

	OnMove.ExecuteIfBound(true);

	if (FVector::DotProduct(forwardVector, velocity) < 0.0f)
		speedPercent -= speedPercent * 0.3f;

	PTR(GetCharacterMovement())->MaxWalkSpeed = StandartSpeed * speedPercent / 100.0f;

	if (!GetMovementComponent()->IsFalling())
	{
		if (GetVelocity().Size() <= StandartSpeed + 1)
			footstepSpeed = FootstepSpeed;
		else
			footstepSpeed = FootstepSpeed / 2.5;

		if (footstepSpeed <= FootstepTimeCount)
			FootstepTimeCount = 0.0;
		else
		{
			FootstepTimeCount += GetWorld()->GetDeltaSeconds();
			return;
		}

		if (FootstepSound)
			UGameplayStatics::PlaySoundAtLocation(this, FootstepSound, GetActorLocation());
	}
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::StopMove(const FInputActionValue& value)
{
	OnMove.ExecuteIfBound(false);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::Look(const FInputActionValue& value)
{
	if (bStopMoving)
		return;

	const FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}
//-----------------------------------------------------------------------------------------------------------
//Getter
UInputAction* AFPSCharacter::GetControlMapIA(const FName& name)
{
	if (ControlMap.Contains(name))
		return *ControlMap.Find(name);

	return nullptr;
}
USkeletalMeshComponent* AFPSCharacter::GetMesh1P() const
{
	return Mesh1P;
}
UCameraComponent* AFPSCharacter::GetFirstPersonCameraComponent() const
{
	return FirstPersonCameraComponent;
}
UInteractComponent* AFPSCharacter::GetInteractComponent()
{
	if (!InteractComponent)
		InteractComponent = FindComponentByClass<UInteractComponent>();
	return InteractComponent;
}
UCameraComponent* AFPSCharacter::GetCameraComponent()
{
	return FirstPersonCameraComponent;
}
UInventoryComponent* AFPSCharacter::GetInventoryComponent()
{
	if(!InventoryComponent)
		InventoryComponent = FindComponentByClass<UInventoryComponent>();
	return InventoryComponent;
}
UEquipmentComponent* AFPSCharacter::GetEquipmentComponent()
{
	if(!EquipmentComponent)
		EquipmentComponent = FindComponentByClass<UEquipmentComponent>();
	return EquipmentComponent;
}
UPlayerStateComponent* AFPSCharacter::GetPlayerStateComponent()
{
	if (!PlayerStateComponent)
		PlayerStateComponent = FindComponentByClass<UPlayerStateComponent>();
	return PlayerStateComponent;
}
UPlayerQuestComponent* AFPSCharacter::GetQuestComponent()
{
	if (!QuestComponent)
		QuestComponent = FindComponentByClass<UPlayerQuestComponent>();
	return QuestComponent;
}
UPlayerSC* AFPSCharacter::GetSkillComponent()
{
	if (!SkillComponent)
		SkillComponent = FindComponentByClass<UPlayerSC>();
	return SkillComponent;
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::RestoreAfterDeath()
{
	if (IsValid(GetStateComponent()))
		GetStateComponent()->RestoreAfterDeath();

	SaveGame();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::TriggerQuestInteract(UQuestInteractTargetMasterDA* questInteractDA)
{
	PTR(GetQuestComponent())->TriggerQuestInteract(questInteractDA);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ActivateCraftSystem()
{
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())
	CraftComponent = NewObject<UCraftComponent>(this, CraftComponentClass);

	CHECK_PTR(CraftComponent)

	CraftComponent->RegisterComponentWithWorld(GetWorld());
	
	PlayerController->CreateWidgetInMainHUD(EStorageType::Craft, CraftComponent);
}
//-----------------------------------------------------------------------------------------------------------
bool AFPSCharacter::DoesHasEmptySlots(int32 numberEmptySlots)
{
	if (GetInventoryComponent())
		return InventoryComponent->DoesHasEmptySlots(numberEmptySlots);

	return false;
}
//-----------------------------------------------------------------------------------------------------------
template <bool bIsStart>
void AFPSCharacter::Sprint()
{
	CHECK_PTR(GetPlayerStateComponent())
	
	if (!PlayerController)
		PlayerController = Cast<AFPSPlayerController>(GetController());

	if (PlayerController && PlayerController->IsPaused())
		PlayerController->bIsFastDrag = bIsStart;

	if (bIsStart)
	{
		if (PlayerStateComponent->GetStateMapElem(EStateName::Stamina) <= 10.0f)
			return;

		SpeedPercent += 100.0f;
	}
	else if(PlayerStateComponent->bIsSprinting)
		SpeedPercent -= 100.0f;
	
		OnChangeSprint.Broadcast(bIsStart);

	
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::Interact()
{
	IItemInteract* interactInterface = nullptr;
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())

	if (PlayerController->IsInventoryWidgetValid())
	{
		PlayerController->CreateWidgetInMainHUD(EStorageType::Inventory);
		return;
	}

	const TWeakObjectPtr<AActor>& target = GetInteractComponent()->GetTargetActor();
	if (target.IsValid() && target->GetClass()->ImplementsInterface(UItemInteract::StaticClass()))
	{
		interactInterface = Cast<IItemInteract>(target);
		if (interactInterface)
			interactInterface->InteractWithActor(this);
		else
			ALARM_LOG
	}
	else
		ALARM_LOG
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ShowHideInventoryWidget()
{
	OnShowHideInventoryWidget.ExecuteIfBound();

	UEventBus::OnWeightCalculation.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ShowHideEscapeMenuWidget()
{
	OnShowHideEscapeMenuWidget.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ShowHideQuestMenu()
{
	OnShowHideQuestMenuWidget.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::UseFastPickUp()
{
	bool bIsHit = false;
	float sphereRadius = 300.0f;
	ACharacterMaster* enemyCharacter = nullptr;
	AActor* enemyActor = nullptr;
	FVector playerLocation = GetActorLocation();
	TArray<AActor*> ignoreActors = {};
	TArray<FHitResult> outHitResult = {};
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};

	objectType.Add(EObjectTypeQuery::ObjectTypeQuery9);

	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this, playerLocation, playerLocation, sphereRadius, 
		objectType, true, ignoreActors, EDrawDebugTrace::None, outHitResult, true);

	if (!bIsHit)
		return;

	for (const FHitResult& item : outHitResult)
	{
		if (item.GetActor() == enemyActor)
			continue;

		enemyActor = item.GetActor();
		enemyCharacter = Cast<ACharacterMaster>(enemyActor);
		if(!enemyCharacter)
			continue;

		enemyCharacter->PickUpEnemyLoot(GetInventoryComponent());
	}
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::PlaySkillAnimation(USkillScrollDA* scrollDA)
{
	CHECK_PTR(scrollDA)
	CHECK_PTR(scrollDA->AttackMontage)
	CHECK_PTR(Mesh1P)
	CHECK_PTR(Mesh1P->GetAnimInstance())

	Mesh1P->GetAnimInstance()->Montage_Play(scrollDA->AttackMontage);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::UseSelectedPotion()
{	
	UEventBus::OnUseSelectedPotion.Broadcast();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::UseSelectedSkill()
{
	if (bIsReload)
		return;

	UEventBus::OnUseSelectedScroll.Broadcast();
}
//-----------------------------------------------------------------------------------------------------------
template<bool bIsShow>
inline void AFPSCharacter::ShowHideFastSelector(const FInputActionInstance& ActionData)
{
	if (!bIsShow)
	{
		bStopFastSelector = false;
		UEventBus::OnShowHideFastSelector.ExecuteIfBound(bIsShow);
	}
	else if(ActionData.GetElapsedTime() >= 0.2f && !bStopFastSelector)
	{
		bStopFastSelector = true;
		UEventBus::OnShowHideFastSelector.ExecuteIfBound(bIsShow);
	}
}
//-----------------------------------------------------------------------------------------------------------
template <int32 weaponIndex>
void AFPSCharacter::EquipWeapon()
{
	OnEquipWeapon.ExecuteIfBound(weaponIndex);
}
template<int32 audusIndex>
void AFPSCharacter::ActivateAudus()
{
	OnActivateAudus.ExecuteIfBound(audusIndex);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::FireTriggered(const FInputActionInstance& ActionData)
{
	if (bStopFastSelector || bIsReload)
		return;

	UEventBus::OnWeaponFire.ExecuteIfBound(this);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ApplyDeath()
{
	Super::ApplyDeath();
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())

	PlayerController->ApplyDeath();
	Sprint<false>();

	bStopFastSelector = false;
	UEventBus::OnShowHideFastSelector.ExecuteIfBound(false);
}
//-----------------------------------------------------------------------------------------------------------
USkeletalMeshComponent* AFPSCharacter::GetCharacterMesh()
{
	return GetMesh1P();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::DealDamage(FDamageStruct& damageStruct, FHitResult hitResult)
{
	if (GetStateComponent() && PlayerStateComponent->bIsDead)
		return;

	PlayerStateComponent->ApplyDamage(damageStruct);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::HitReaction()
{
	Super::HitReaction();
	UCharacterMasterDA* characterDA = GetConfigDA<UCharacterMasterDA>();
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())

	PlayerController->WidgetHealthHitReaction();

	CHECK_PTR(characterDA)
	CHECK_PTR(characterDA->SoundHit)
	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), characterDA->SoundHit, GetActorLocation()); 
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::ApplyInteract(EStorageType storageType, UStorageComponent* storageComponent)
{
	CHECK_CAST(PlayerController, AFPSPlayerController, GetController())

	PlayerController->CreateWidgetInMainHUD(storageType, storageComponent);

	UEventBus::OnWeightCalculation.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
bool AFPSCharacter::PickUpItem(int32& itemCount, UItemMasterDA* itemDA)
{
	if (!GetInventoryComponent())
	{
		ALARM_LOG
			return false;
	}
	return InventoryComponent->PickUpItem(itemCount, itemDA);
}
void AFPSCharacter::TESTING_PickUpItem(int32 itemCount, UItemMasterDA* itemDA, int32 itemLevel, FStatValueStruct statValue)
{
	CHECK_PTR(GetInventoryComponent())

	InventoryComponent->PickUpItem(itemCount, itemDA, itemLevel, statValue);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSCharacter::PickUpCurrency(const FCurrency& currencyStruct)
{
	if (!GetInventoryComponent())
	{
		ALARM_LOG
			return;
	}

	InventoryComponent->PickUpItem(currencyStruct);
}
//-----------------------------------------------------------------------------------------------------------
