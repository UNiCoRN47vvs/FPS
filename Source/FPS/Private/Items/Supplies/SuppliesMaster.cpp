#include "Items/Supplies/SuppliesMaster.h"
//-----------------------------------------------------------------------------------------------------------
ASuppliesMaster::ASuppliesMaster()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComponent;
}
//-----------------------------------------------------------------------------------------------------------
void ASuppliesMaster::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetSimulatePhysics(true);
}
//-----------------------------------------------------------------------------------------------------------
void ASuppliesMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	InitParams();
}
//-----------------------------------------------------------------------------------------------------------
void ASuppliesMaster::InitParams(UItemMasterDA* ItemDA)
{
	Super::InitParams(ItemDA);
	USuppliesMasterDA* suppliesDA = GetConfigDA<USuppliesMasterDA>();
	CHECK_PTR(suppliesDA)
	CHECK_PTR(suppliesDA->StaticMesh.LoadSynchronous())
	
	StaticMeshComponent->SetStaticMesh(suppliesDA->StaticMesh.Get());
}
//-----------------------------------------------------------------------------------------------------------