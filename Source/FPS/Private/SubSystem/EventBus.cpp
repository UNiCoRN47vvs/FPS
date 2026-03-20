#include "SubSystem/EventBus.h"
//-----------------------------------------------------------------------------------------------------------
#pragma region
TDelegate<void()> UEventBus::OnSaveGame;
TDelegate<void()> UEventBus::OnHitEnemyWidgetAnim;
TDelegate<void()> UEventBus::OnWeightCalculation;
TDelegate<void()> UEventBus::OnUpdateCurrencyWidget;
TDelegate<void()> UEventBus::OnApplySelectedScroll;
TDelegate<int32()> UEventBus::OnGetDragIndex;
TDelegate<UStorageComponent*()> UEventBus::OnGetDragStorage;
TDelegate<UEquipmentComponent* ()> UEventBus::OnGetEquipmentComponent;
TDelegate<const TMap<FKey, FText>&()> UEventBus::OnGetKeyInfo;
TDelegate < TMap<FName, bool>& ()> UEventBus::OnGetSaveInfoMap;
TDelegate<TMap<EStateName, float>&()> UEventBus::OnGetPlayerStateMap;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region One Param
TDelegate<void(bool)> UEventBus::OnShowHideFastSelector;
TDelegate<void(bool)> UEventBus::OnShowFPS;
TDelegate<void(AFPSCharacter*)> UEventBus::OnWeaponFire;
TDelegate<void(UQuestInteractTargetMasterDA*)> UEventBus::OnUseQuestInteract;
TDelegate<void(UItemMasterDA*)> UEventBus::OnSelectorPotion;
TDelegate<void(UItemMasterDA*)> UEventBus::OnSelectorScroll;
TDelegate<void(UItemMasterDA*)> UEventBus::OnActivateAudus;
TDelegate<void(UStorageComponent*)> UEventBus::OnCreateDialogWidget;
TDelegate<float(EElementsType)> UEventBus::OnPlayerElementsChance;
TDelegate<void(const float)> UEventBus::OnUpdateWeight;
TDelegate<void(const FItemInvStruct&)> UEventBus::OnFastPickUp;
TDelegate<void(const FName&)> UEventBus::OnClickInfoButton;
TDelegate<void(TArray<FStorageTab>&)> UEventBus::OnUpgradeSave;
TDelegate<UInformationWidget* (FItemInvStruct)> UEventBus::OnShowInformationWidget;
TDelegate<UInformationWidget* (TMap<EStateName, float>&)> UEventBus::OnShowInformationStateWidget;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region Two Params
TDelegate<void(bool, FText&)> UEventBus::OnTriggerInteractWidget;
TDelegate<void(bool, EItemType)> UEventBus::OnPlaySlotAnimationWidget;
TDelegate<void(int32, int32)> UEventBus::OnUpdateAmmoWidget;
TDelegate<void(float, float)> UEventBus::OnPotionCoolDown;
TDelegate<void(float, float)> UEventBus::OnScrollCoolDown;
TDelegate<void(const TMap<EStateName, float>&)> UEventBus::OnUseConsumableSupplies;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region Three Params
TDelegate<void(EStorageType, int32, const TArray<FItemInvStruct>&)> UEventBus::OnSetItemFromIndexWidget;
TDelegate<void(UStorageComponent*, int32, bool)> UEventBus::OnDragDropOperation;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region Multicast
TMulticastDelegate<void()> UEventBus::OnUseSelectedPotion;
TMulticastDelegate<void()> UEventBus::OnUseSelectedScroll;
TMulticastDelegate<void()> UEventBus::OnUpdateKeyInfo;
TMulticastDelegate<void()> UEventBus::OnGeneralWidgetClose;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region Multicast One Param
TMulticastDelegate<void(UEnemyMasterDA*)> UEventBus::OnEnemyDeath;
TMulticastDelegate<void(USkillScrollDA*)> UEventBus::OnPlayerSkill;
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region Multicast Two Param
TMulticastDelegate<void(UItemMasterDA*, const TArray<FItemInvStruct>&)> UEventBus::OnUpdateInfoFastSelectorPotion;
TMulticastDelegate<void(UItemMasterDA*, const TArray<FItemInvStruct>&)> UEventBus::OnUpdateInfoFastSelectorScroll;
#pragma endregion