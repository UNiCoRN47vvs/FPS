#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Character.h"
#include "Interfaces/DeathInterface.h"
#include "Enums/StorageType.h"
#include "Config/CharacterMasterDA.h"
#include "CharacterMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStateMasterComponent;
class UChestComponent;
class UStorageComponent;
class UInventoryComponent;
class UInteractComponent;
class UItemMasterDA;
class UQuestInteractTargetMasterDA;
struct FDamageStruct;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ACharacterMaster : public ACharacter, public IDeathInterface
{
	GENERATED_BODY()

public:
	
	ACharacterMaster();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//**************************
	//Interfaces
	virtual void ApplyDeath();
	//**************************
	virtual void DealDamage(FDamageStruct& damageStruct, FHitResult hitResult = {});
	virtual USkeletalMeshComponent* GetCharacterMesh();
	virtual void HitReaction();
	virtual void ApplyInteract(EStorageType StorageType, UStorageComponent* StorageComponent = nullptr);
	virtual bool PickUpItem(int32& ItemCount, UItemMasterDA* ItemDA);
	virtual void TriggerQuestInteract(UQuestInteractTargetMasterDA* QuestInteractDA);
	virtual void PickUpEnemyLoot(UInventoryComponent* inventoryComponent);
	//**************************
	//Getters
	UStateMasterComponent* GetStateComponent();
	UChestComponent* GetChestComponent();
	virtual UInteractComponent* GetInteractComponent();
	virtual UInventoryComponent* GetInventoryComponent();
	template <typename DataAssetClass>	DataAssetClass* GetConfigDA()
	{
		return Cast<DataAssetClass>(DataAssetConfig);
	};
	//**************************

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset Config")	UCharacterMasterDA* DataAssetConfig;
	UStateMasterComponent* StateMasterComponent;
	UChestComponent* ChestComponent;
private:
};
//-----------------------------------------------------------------------------------------------------------


