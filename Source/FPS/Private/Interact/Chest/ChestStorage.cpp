#include "Interact/Chest/ChestStorage.h"
#include "Character/CharacterMaster.h"
//-----------------------------------------------------------------------------------------------------------
AChestStorage::AChestStorage()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	StaticMeshComponent->SetupAttachment(ItemScene);
}
//-----------------------------------------------------------------------------------------------------------
void AChestStorage::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	CHECK_PTR(PlayerCharacter)

	PlayerCharacter->ApplyInteract(EStorageType::Chest);
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct AChestStorage::GetInteractInfo()
{
	return InteractInfo;
}
//-----------------------------------------------------------------------------------------------------------