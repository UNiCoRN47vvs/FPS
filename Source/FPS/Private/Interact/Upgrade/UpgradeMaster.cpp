#include "Interact/Upgrade/UpgradeMaster.h"
#include "Character/CharacterMaster.h"
#include "ActorComponents/Upgrade/UpgradeComponent.h"
//-----------------------------------------------------------------------------------------------------------
AUpgradeMaster::AUpgradeMaster()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	StaticMeshComponent->SetupAttachment(ItemScene);
}
//-----------------------------------------------------------------------------------------------------------
void AUpgradeMaster::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName(TEXT("Upgrade")));
}
//-----------------------------------------------------------------------------------------------------------
UUpgradeComponent* AUpgradeMaster::GetUpgradeComponent()
{
	if (!UpgradeComponent)
		UpgradeComponent = FindComponentByClass<UUpgradeComponent>();

	return UpgradeComponent;
}
//-----------------------------------------------------------------------------------------------------------
void AUpgradeMaster::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	CHECK_PTR(PlayerCharacter)

	PlayerCharacter->ApplyInteract(EStorageType::Upgrade, GetUpgradeComponent());
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct AUpgradeMaster::GetInteractInfo()
{
	return InteractInfo;
}
//-----------------------------------------------------------------------------------------------------------