#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Containers/Map.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Enums/StateName.h"
#include "Enums/ItemType.h"
#include "Enums/StorageType.h"
#include "Enums/ElementsType.h"
#include "EventBus.generated.h"
//-----------------------------------------------------------------------------------------------------------
#pragma region Forward Declaration
class UStorageComponent;
class UQuestInteractTargetMasterDA;
class UEnemyMasterDA;
class AFPSCharacter;
class UItemMasterDA;
class USkillScrollDA;
class UStorageComponent;
class UEquipmentComponent;
class UInformationWidget;
struct FItemInvStruct;
struct FStorageTab;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEventBus : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
#pragma region
	static TDelegate<void()> OnSaveGame;
	static TDelegate<void()> OnHitEnemyWidgetAnim;
	static TDelegate<void()> OnWeightCalculation;
	static TDelegate<void()> OnUpdateCurrencyWidget;
	static TDelegate<void()> OnApplySelectedScroll;
	static TDelegate<int32()> OnGetDragIndex;
	static TDelegate<UStorageComponent* ()> OnGetDragStorage;
	static TDelegate<UEquipmentComponent* ()> OnGetEquipmentComponent;
	static TDelegate<const TMap<FKey, FText>&()> OnGetKeyInfo;
	static TDelegate<TMap<FName, bool>&()> OnGetSaveInfoMap;
	static TDelegate<TMap<EStateName, float>& ()> OnGetPlayerStateMap;
#pragma endregion

#pragma region One Param
	static TDelegate<void(bool)> OnShowHideFastSelector;
	static TDelegate<void(bool)> OnShowFPS;
	static TDelegate<void(AFPSCharacter*)> OnWeaponFire;
	static TDelegate<void(UQuestInteractTargetMasterDA*)> OnUseQuestInteract;
	static TDelegate<void(UItemMasterDA*)> OnSelectorPotion;
	static TDelegate<void(UItemMasterDA*)> OnSelectorScroll;
	static TDelegate<void(UItemMasterDA*)> OnActivateAudus;
	static TDelegate<void(UStorageComponent*)> OnCreateDialogWidget;
	static TDelegate<float(EElementsType)> OnPlayerElementsChance;
	static TDelegate<void(const float)> OnUpdateWeight;
	static TDelegate<void(const FItemInvStruct&)> OnFastPickUp;
	static TDelegate<void(const FName&)> OnClickInfoButton;
	static TDelegate<void(TArray<FStorageTab>&)> OnUpgradeSave;
	static TDelegate<UInformationWidget*(FItemInvStruct)> OnShowInformationWidget;
	static TDelegate<UInformationWidget*(TMap<EStateName, float>&)> OnShowInformationStateWidget;
#pragma endregion

#pragma region Two Params
	static TDelegate<void(bool, FText&)> OnTriggerInteractWidget;
	static TDelegate<void(bool, EItemType)> OnPlaySlotAnimationWidget;
	static TDelegate<void(int32, int32)> OnUpdateAmmoWidget;
	static TDelegate<void(float, float)> OnPotionCoolDown;
	static TDelegate<void(float, float)> OnScrollCoolDown;
	static TDelegate<void(const TMap<EStateName, float>&)> OnUseConsumableSupplies;
#pragma endregion

#pragma region Three Params
	static TDelegate<void(EStorageType, int32, const TArray<FItemInvStruct>&)> OnSetItemFromIndexWidget;
	static TDelegate<void(UStorageComponent*, int32, bool)> OnDragDropOperation;
#pragma endregion

#pragma region Multicast
	static TMulticastDelegate<void()> OnUseSelectedPotion;
	static TMulticastDelegate<void()> OnUseSelectedScroll;
	static TMulticastDelegate<void()> OnUpdateKeyInfo;
	static TMulticastDelegate<void()> OnGeneralWidgetClose;
#pragma endregion

#pragma region Multicast One Param
	static TMulticastDelegate<void(UEnemyMasterDA*)> OnEnemyDeath;
	static TMulticastDelegate<void(USkillScrollDA*)> OnPlayerSkill;
#pragma endregion

#pragma region Multicast Two Param
	static TMulticastDelegate<void(UItemMasterDA*, const TArray<FItemInvStruct>&)> OnUpdateInfoFastSelectorPotion;
	static TMulticastDelegate<void(UItemMasterDA*, const TArray<FItemInvStruct>&)> OnUpdateInfoFastSelectorScroll;
#pragma endregion
	
};
//-----------------------------------------------------------------------------------------------------------