#include "Character/CharacterMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "ActorComponents/Chest/ChestComponent.h"
//-----------------------------------------------------------------------------------------------------------
ACharacterMaster::ACharacterMaster()
{
	PrimaryActorTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
bool ACharacterMaster::PickUpItem(int32& ItemCount, UItemMasterDA* ItemDA)
{
	return false;
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
//Getters
UStateMasterComponent* ACharacterMaster::GetStateComponent()
{
	if (!StateMasterComponent)
		StateMasterComponent = FindComponentByClass<UStateMasterComponent>();
	return StateMasterComponent;
}
UChestComponent* ACharacterMaster::GetChestComponent()
{
	if(!ChestComponent)
		ChestComponent = FindComponentByClass<UChestComponent>();
	return ChestComponent;
}
//-----------------------------------------------------------------------------------------------------------
UInteractComponent* ACharacterMaster::GetInteractComponent()
{
	return nullptr;
}
//-----------------------------------------------------------------------------------------------------------
UInventoryComponent* ACharacterMaster::GetInventoryComponent()
{
	return nullptr;
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::TriggerQuestInteract(UQuestInteractTargetMasterDA* QuestInteractDA)
{
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::PickUpEnemyLoot(UInventoryComponent* inventoryComponent)
{
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::ApplyDeath()
{
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::DealDamage(FDamageStruct& damageStruct, FHitResult hitResult)
{
}
//-----------------------------------------------------------------------------------------------------------
USkeletalMeshComponent* ACharacterMaster::GetCharacterMesh()
{
	return nullptr;
}
//-----------------------------------------------------------------------------------------------------------
void ACharacterMaster::HitReaction()
{
}
void ACharacterMaster::ApplyInteract(EStorageType StorageType, UStorageComponent* StorageComponent)
{
}
//-----------------------------------------------------------------------------------------------------------

