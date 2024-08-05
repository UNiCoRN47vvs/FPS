#include "Items/Supplies/SuppliesMaster.h"
//-----------------------------------------------------------------------------------------------------------
ASuppliesMaster::ASuppliesMaster()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	StaticMeshComponent->SetupAttachment(ItemScene);
	ItemSphereComponent->SetupAttachment(StaticMeshComponent);
}
