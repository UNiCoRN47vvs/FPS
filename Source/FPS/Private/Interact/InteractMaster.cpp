#include "Interact/InteractMaster.h"
//-----------------------------------------------------------------------------------------------------------
AInteractMaster::AInteractMaster()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemScene = CreateDefaultSubobject<USceneComponent>(TEXT("Item Scene Component"));

	ItemScene->SetupAttachment(RootComponent);
}
//-----------------------------------------------------------------------------------------------------------
void AInteractMaster::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void AInteractMaster::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct AInteractMaster::GetInteractInfo()
{
	return FInteractStruct();
}
//-----------------------------------------------------------------------------------------------------------

