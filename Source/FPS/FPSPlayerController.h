#pragma once

#include "FPS/FPS.h"
#include "GameFramework/PlayerController.h"
#include "Enums/StorageType.h"
#include "Enums/ItemType.h"
#include "FPSPlayerController.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInputMappingContext;
class UMainHUDWidget;
class UStorageWidget;
class AFPSCharacter;
class UStorageComponent;
class UEquipmentComponent;
class UInventoryComponent;
class UChestComponent;
class UInventorySlotWidget;
class UItemMasterDA;
class UWorldRuler;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	bool IsInventoryWidgetValid();
	//**************************
	//Getters
	bool GetApplyFastDropInfo(const EStorageType storageType, FItemInvStruct item);
	bool SpawnSystemIsBlocking();
	//**************************
	bool IsStoreValid();

	void WidgetHealthHitReaction();
	void CreateWidgetInMainHUD(EStorageType widgetType, UStorageComponent* storageComponent = nullptr);
	void RemoveLoadScreen(const bool bIsNewGame = false);
	void SetWidgetInputMode(bool bIsShow);
	void SetWaveTimeCount();
	void ApplyDeath();

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext* InputMappingContext;
	UPROPERTY() UMainHUDWidget* MainHUD;
	TWeakObjectPtr<UUserWidget> PopupMenu;
	uint8 bIsFastDrag : 1;
	uint8 bIsHome : 1;
protected:
	virtual void BeginPlay() override;
	UFUNCTION() void ApplyDeathSubFunc1();
	UFUNCTION() void ApplyDeathSubFunc2();
	UFUNCTION() void UpdateTimeCount(int32 count);
	UFUNCTION() void UpdateWaveCount(int32 count);
	UFUNCTION() void UpdateEnemyCount(int32 count);
private:
	void ShowHideQuestMenuWidget();
	UPROPERTY() UUserWidget* LoadScreen;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() UWorldRuler* WorldRuler;
	UPROPERTY(EditDefaultsOnly, Category = "FPS_P_C") TSubclassOf<UMainHUDWidget> MainHUDWidget;
	UPROPERTY(EditAnywhere, Category = "FPS_P_C") TSubclassOf<UUserWidget> WBPLoadScreen;
	UPROPERTY(EditAnywhere, Category = "FPS_P_C") TSubclassOf<UUserWidget> FirstQuestWidgetClass;

};
//-----------------------------------------------------------------------------------------------------------