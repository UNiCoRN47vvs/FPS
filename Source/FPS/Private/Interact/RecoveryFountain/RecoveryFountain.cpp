#include "Interact/RecoveryFountain/RecoveryFountain.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CharacterMaster.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
//-----------------------------------------------------------------------------------------------------------
ARecoveryFountain::ARecoveryFountain()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));

	PrimaryActorTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct ARecoveryFountain::GetInteractInfo()
{	
	return InteractStruct;
}
//-----------------------------------------------------------------------------------------------------------
void ARecoveryFountain::InteractWithActor(ACharacterMaster* PlayerCharacter)
{

	UInventoryComponent* inventoryComponent = nullptr;
	FCurrency price = {};
	price.Sulfur = InteractCost;

	inventoryComponent = PlayerCharacter->FindComponentByClass<UInventoryComponent>();

	if (inventoryComponent && inventoryComponent->DoesHaveEnoughCurrency(price))
		inventoryComponent->SubtractCurrency(price);
	else
		return; //TODO :: ƒобавить оповещение о нехватке средств

	UGameplayStatics::PlaySound2D(this, InteractSound);

	PlayerCharacter->GetStateComponent()->RestoreAfterDeath();
}
//-----------------------------------------------------------------------------------------------------------
void ARecoveryFountain::BeginPlay()
{
	Super::BeginPlay();

	if (FMath::RandRange(0.0f, 100.0f) > SpawnChance)
		Destroy();

	if (InteractCost > 0.0f)
		InteractStruct.ItemName = FString(" for : ") + FString::SanitizeFloat(InteractCost) + FString(" Sulfur");
}
//-----------------------------------------------------------------------------------------------------------

