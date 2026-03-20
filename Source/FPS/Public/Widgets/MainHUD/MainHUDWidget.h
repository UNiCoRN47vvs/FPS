#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "ActorComponents/State/PlayerStateComponent.h"
#include "Components/Border.h"
#include "Enums/StorageType.h"
#include "Enums/ItemType.h"
#include "MainHUDWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
#pragma region Forward Declaration
class UProgressBarWidget;
class UInventoryWidget;
class UStorageComponent;
class AFPSCharacter;
class AFPSPlayerController;
class UAmmoWidget;
class IInteractInfo;
class UElementalEffects;
class UTextBlock;
class UWaveEnemyCountWidget;
class UGenegalStorageWidget;
class UInventorySlotWidget;
class UEscapeMenuWidget;
class UFramePerSecondWidget;
class UDialogWidget;
class UItemMasterDA;
class UPopUpQuestGoalWidget;
class UVerticalBox;
class UGeneralCenterWidget;
class UFastSelectorWidget;
class UPopUpMasterWidget;
struct FQuest;
struct FItemInvStruct;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void HealthHitReaction();
	//**************************
	//Getters
	FORCEINLINE UStorageComponent* GetDragStorage();
	FORCEINLINE int32 GetDragIndex() const;
	UStorageComponent* GetCurrentActiveStorage();
	const TMap<FKey, FText>& GetKeyInfo();
	void UpdateCurrentStorageSlot();
	//**************************
	void CreateWidgetByType(EStorageType widgetType, UStorageComponent* storageComponent = nullptr, AActor* questGiverActor = nullptr);
	void ShowHideDeathBorder(bool bIsShow);
	void CreateRemoveEscapeMenu(bool bIsCreate);
	void PlayHitEnemyAnimation();
	void ShowHideFrameRate(bool bIsShow);
	//**************************
	//Delegate Func
	UFUNCTION() void DragDropOperation(UStorageComponent* storageComponent, int32 index, bool bIsDrop);
	UFUNCTION() void TriggerInteractWidget(bool bIsShow, FText& text);
	UFUNCTION() void CreateDialogWidget(UStorageComponent* storageComp);
	//**************************
	bool IsStoreValid();

	void UpdateTimeCount(int32 Count);
	void UpdateWaveCount(int32 Count);
	void UpdateEnemyCount(int32 Count);

	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UProgressBarWidget* WBPHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UProgressBarWidget* WBPStamina;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UProgressBarWidget* WBPMana;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UWaveEnemyCountWidget* WBPWaveEnemyCount;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UBorder* CenterPoint;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UBorder* DeathBorder;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UVerticalBox* CenterVerticalBox;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UVerticalBox* PopUpQuestBox;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UVerticalBox* PopUpFastPickUpBox;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UTextBlock* InteractWidgetTB;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UAmmoWidget* WBPAmmo;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UElementalEffects* WBPElementalEffects;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidget)) UFastSelectorWidget* WBPFastSelector;

	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidgetAnim), Transient) UWidgetAnimation* HealthHitAnimation;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD", meta = (BindWidgetAnim), Transient) UWidgetAnimation* HitToEnemyAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Main HUD") UEscapeMenuWidget* WBPEscapeMenu;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD") UFramePerSecondWidget* WBPFrameRate;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD") UDialogWidget* WBPDialog;
	UPROPERTY(BlueprintReadOnly, Category = "Main HUD") UGeneralCenterWidget* WBPGeneralCenter;

	TDelegate<void(bool)> OnSetWidgetInputMode;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION() void QuestGoal(FQuest questStruct);
	UFUNCTION()	void UpdateProgressBar(EStateName stateName, float currentValue, float maxValue);
	UFUNCTION() void CloseGeneral();
	void FastPickUpPopUp(const FItemInvStruct& itemStruct);
private:
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() AFPSPlayerController* PlayerController;
	UPROPERTY() UStorageComponent* DragStorage;
	UPROPERTY() UStorageComponent* DropStorage;
	UPROPERTY() UGenegalStorageWidget* ActiveStorageWidget;
	int32 DragIndex;
	int32 DropIndex;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UInventoryWidget> InventoryWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UEscapeMenuWidget> EscapeMenuWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UFramePerSecondWidget> FrameWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UDialogWidget> DialogWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UGeneralCenterWidget> GeneralCenterWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UPopUpQuestGoalWidget> PopUpQuestWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TSubclassOf<UPopUpMasterWidget> PopUpFastPickUpWidget;
	UPROPERTY(EditAnywhere, Category = "Main HUD") TMap<FKey, FText> KeyInfo;
	
};
//-----------------------------------------------------------------------------------------------------------