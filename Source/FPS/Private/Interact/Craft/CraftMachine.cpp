#include "Interact/Craft/CraftMachine.h"
#include "Components/StaticMeshComponent.h"
#include "FPS/FPSCharacter.h"
//-----------------------------------------------------------------------------------------------------------
ACraftMachine::ACraftMachine()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));

	StaticMeshComponent->SetupAttachment(ItemScene);
}
//-----------------------------------------------------------------------------------------------------------
void ACraftMachine::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	AFPSCharacter* character = Cast<AFPSCharacter>(PlayerCharacter);

	PTR(character)->ActivateCraftSystem();
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct ACraftMachine::GetInteractInfo()
{
	return InteractInfo;
}
//-----------------------------------------------------------------------------------------------------------
void ACraftMachine::BeginPlay()
{
	Super::BeginPlay();
	
}
//-----------------------------------------------------------------------------------------------------------

