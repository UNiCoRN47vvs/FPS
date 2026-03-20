#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Enums/StorageType.h"
#include "Enums/ItemType.h"
#include "GeneralCenterWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UWidgetSwitcher;
class UInventoryButtonWidget;
class UInventoryWidget;
class UQuestsWidget;
class AFPSCharacter;
class UStorageComponent;
class UMainHUDWidget;
class UButton;
class UGenegalStorageWidget;
class UInformationStandWidget;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UGeneralCenterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//**************************
	//Getters
	UStorageComponent* GetCurrentActiveStorage();
	//**************************
	void InitGeneralCenterWidget(AFPSCharacter* playerCharacter, EStorageType widgetType, UStorageComponent* storageComponent, AActor* questGiverActor, UMainHUDWidget* HUD = nullptr);
	UFUNCTION() void SetItemFromIndexWidget(EStorageType type, const int32 index, const TArray<FItemInvStruct>& storage);
	
	void UpdateCurrentStorageSlot();
	bool IsStoreValid();

	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UWidgetSwitcher* WidgetSwitcher;
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UInventoryButtonWidget* InventoryButton;
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UInventoryButtonWidget* QuestsButton;
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UInventoryButtonWidget* InfoWidgetButton;
															 
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UInventoryWidget* WBPInventory;
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UQuestsWidget* WBPQuests;
	UPROPERTY(BlueprintReadOnly, Category = "G_C", meta = (BindWidget)) UInformationStandWidget* WBPInformation;
															 
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION() void ShowInventory();
	UFUNCTION() void ShowQuests();
	UFUNCTION() void ShowInfoWidget();
	void ClickInfoButton(const FName& name);
private:
	uint8 bIsNotFirstInvInit : 1;
	uint8 bIsNotFirstQuestsInit : 1;
	uint8 bIsNotFirstInfoInit : 1;

	EStorageType StorageType;
	UPROPERTY() UGenegalStorageWidget* ActiveStorageWidget;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() UStorageComponent* StorageComponent;
	UPROPERTY() AActor* QuestGiver;
	UPROPERTY() UMainHUDWidget* MainHUD;
};
//-----------------------------------------------------------------------------------------------------------
