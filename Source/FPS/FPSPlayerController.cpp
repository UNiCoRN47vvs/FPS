#include "FPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/WorldRuler.h"
#include "FirstPerson/FPSGameInstance.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Chest/ChestComponent.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Widgets/GeneralCenterWidget/GeneralCenterWidget.h"
#include "Widgets/FirstQuest/FirstQuestWidget.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bIsHome = true;
	LoadScreen = CreateWidget<UUserWidget>(GetWorld(), WBPLoadScreen);
	if (LoadScreen)
		LoadScreen->AddToViewport(999999999);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (subsystem && UFPSGameInstance::OnGetInputMapingContext.IsBound())
	{
		subsystem->AddMappingContext(UFPSGameInstance::OnGetInputMapingContext.Execute(), 0);
		subsystem->GetUserSettings()->RegisterInputMappingContext(UFPSGameInstance::OnGetInputMapingContext.Execute());
	}

	MainHUD = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidget);
	if (MainHUD)
		MainHUD->AddToViewport();

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetPawn())

	PlayerCharacter->OnShowHideInventoryWidget.BindLambda([&]() 
		{
			if (!MainHUD || MainHUD->WBPEscapeMenu)
				return;

			if (!MainHUD->WBPGeneralCenter)
				MainHUD->CreateWidgetByType(EStorageType::Inventory);
			else
				MainHUD->CreateWidgetByType(EStorageType::Chest);
		});

	PlayerCharacter->OnShowHideEscapeMenuWidget.BindLambda([&]()
		{
			if (!MainHUD || MainHUD->WBPGeneralCenter)
				return;

			if (MainHUD->WBPEscapeMenu)
				MainHUD->CreateRemoveEscapeMenu(false);
			else
				MainHUD->CreateRemoveEscapeMenu(true);
		});

	PlayerCharacter->OnShowHideQuestMenuWidget.BindUObject(this, &AFPSPlayerController::ShowHideQuestMenuWidget);
	MainHUD->OnSetWidgetInputMode.BindUObject(this, &AFPSPlayerController::SetWidgetInputMode);
	SetWidgetInputMode(false);

	Public_Beta_Controller_Block
}
//-----------------------------------------------------------------------------------------------------------
bool AFPSPlayerController::IsInventoryWidgetValid()
{
	if (!MainHUD)
	{
		ALARM_LOG
		return false;
	}
	
	if (IsValid(MainHUD->WBPGeneralCenter))
		return true;

	return false;
}
//-----------------------------------------------------------------------------------------------------------
bool AFPSPlayerController::GetApplyFastDropInfo(const EStorageType storageType, FItemInvStruct item)
{
	UItemMasterDA* itemDA = nullptr;
	UStorageComponent* storageComponent = nullptr;
	UInventoryComponent* inventoryComponent = nullptr;

	if (!MainHUD)
	{
		ALARM_LOG
		return false;
	}

	itemDA = Cast<UItemMasterDA>(item.ItemDA);
	if (!itemDA)
	{
		ALARM_LOG
		return false;
	}

	switch (storageType)
	{
	case EStorageType::Chest:
	case EStorageType::TreasureInventory:
		inventoryComponent = GetPawn()->FindComponentByClass<UInventoryComponent>();

		if (!inventoryComponent || !inventoryComponent->PickUpItem(item.ItemCount, itemDA, item.ItemLevel, item.StatValue))
			return false;
		
		break;

	case EStorageType::Inventory:
		storageComponent = MainHUD->GetCurrentActiveStorage();
		if (!storageComponent)
		{
			ALARM_LOG
			return false;
		}

		if (!storageComponent->PickUpItem(item.ItemCount, itemDA, item.ItemLevel, item.StatValue))
			return false;
		
		break;

	case EStorageType::Upgrade:
	case EStorageType::Equipment:
	default:
		break;
	}

	MainHUD->UpdateCurrentStorageSlot();
	return true;
}
bool AFPSPlayerController::SpawnSystemIsBlocking()
{
	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		if (!WorldRuler)
		{
			ALARM_LOG
			return false;
		}
	}

	return WorldRuler->bIsBlocking;
}
//-----------------------------------------------------------------------------------------------------------
bool AFPSPlayerController::IsStoreValid()
{
	if (!IsValid(MainHUD))
		return false;

	return MainHUD->IsStoreValid();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::WidgetHealthHitReaction()
{
	CHECK_PTR(MainHUD)
	
	MainHUD->HealthHitReaction();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::CreateWidgetInMainHUD(EStorageType widgetType, UStorageComponent* storageComponent)
{
	PTR(MainHUD)->CreateWidgetByType(widgetType, storageComponent);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::RemoveLoadScreen(const bool bIsNewGame)
{
	if (IsValid(LoadScreen))
	{
		LoadScreen->RemoveFromParent();
		LoadScreen = nullptr;
	}

	if (bIsNewGame)
	{
		UFirstQuestWidget* firstQuestWidget = CreateWidget<UFirstQuestWidget>(this, FirstQuestWidgetClass);
		firstQuestWidget->AddToViewport(9999);
		PTR(firstQuestWidget)->InitFirstQuest(MainHUD);
	}

	GetCharacter()->EnableInput(this);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::SetWidgetInputMode(bool bIsShow)
{
	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetPawn())

	bShowMouseCursor = bIsShow;
	if (bIsShow)
	{
		SetInputMode(FInputModeGameAndUI());
		SetPause(true);
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		SetPause(false);
	}

	if (PopupMenu.IsValid())
	{
		PopupMenu->RemoveFromParent();
		PopupMenu = nullptr;
	}
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::SetWaveTimeCount()
{
	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	WorldRuler->OnTimeCount.Unbind();
	WorldRuler->OnWaveCount.Unbind();
	WorldRuler->OnEnemyCount.Unbind();

	WorldRuler->OnTimeCount.BindUObject(this, &AFPSPlayerController::UpdateTimeCount);
	WorldRuler->OnWaveCount.BindUObject(this, &AFPSPlayerController::UpdateWaveCount);
	WorldRuler->OnEnemyCount.BindUObject(this, &AFPSPlayerController::UpdateEnemyCount);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::ApplyDeath()
{
	CHECK_PTR(MainHUD)

	FTimerHandle timerHandle = {};

	GetCharacter()->DisableInput(this);
	MainHUD->ShowHideDeathBorder(true);

	if (PopupMenu.IsValid())
	{
		PopupMenu->RemoveFromParent();
		PopupMenu = nullptr;
	}

	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AFPSPlayerController::ApplyDeathSubFunc1, 2.0, false);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::ApplyDeathSubFunc1()
{
	FLatentActionInfo latent;

	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	latent.CallbackTarget = this;
	latent.ExecutionFunction = FName("ApplyDeathSubFunc2");
	latent.Linkage = 0;
	latent.UUID = FMath::Rand();

	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, WorldRuler->GetMainHUB(), true, false, latent);
}
void AFPSPlayerController::ApplyDeathSubFunc2()
{
	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetCharacter())

	WorldRuler->TimerToHome(0);
	PlayerCharacter->EnableInput(this);
	MainHUD->ShowHideDeathBorder(false);
	PlayerCharacter->RestoreAfterDeath();
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::UpdateTimeCount(int32 count)
{
	PTR(MainHUD)->UpdateTimeCount(count);
}
void AFPSPlayerController::UpdateWaveCount(int32 count)
{
	PTR(MainHUD)->UpdateWaveCount(count);
}
void AFPSPlayerController::UpdateEnemyCount(int32 count)
{
	PTR(MainHUD)->UpdateEnemyCount(count);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSPlayerController::ShowHideQuestMenuWidget()
{
	PTR(MainHUD)->CreateWidgetByType(EStorageType::Quests);
}
//-----------------------------------------------------------------------------------------------------------