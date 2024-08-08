#include "Items/Supplies/SuppliesMaster.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Interact/InteractComponent.h"
#include "Widgets/Interact/InfoInteractWidget.h"
//-----------------------------------------------------------------------------------------------------------
ASuppliesMaster::ASuppliesMaster()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	StaticMeshComponent->SetupAttachment(ItemScene);
	ItemSphereComponent->SetupAttachment(StaticMeshComponent);
}
//-----------------------------------------------------------------------------------------------------------
void ASuppliesMaster::BeginPlay()
{
	Super::BeginPlay();
	UStaticMesh* LocalStaticMesh = ItemSuppliesInfo.StaticMesh.LoadSynchronous();
	if (LocalStaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(LocalStaticMesh);
		StaticMeshComponent->SetSimulatePhysics(true);
	}
}
//-----------------------------------------------------------------------------------------------------------
void ASuppliesMaster::InteractWithActor(AFPSCharacter* PlayerCharacter)
{
	Super::InteractWithActor(PlayerCharacter);
	if (!PlayerCharacter)
		return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, PlayerInterface = nullptr!")));

	FItemInvStruct LocalItemStruct;
	LocalItemStruct.ItemValue    = ItemSuppliesInfo.UseValue;
	LocalItemStruct.ItemCount    = ItemInfo.ItemCount;
	LocalItemStruct.ItemCountMax = ItemInfo.ItemCountMax;
	LocalItemStruct.ItemName     = ItemInfo.ItemName;
	LocalItemStruct.ItemDesc     = ItemInfo.ItemDesc;
	LocalItemStruct.ItemIcon     = ItemInfo.ItemIcon;
	LocalItemStruct.ItemClass    = ItemInfo.ItemClass;

	if (PlayerCharacter->GetInventoryComponent()->PickUpItem(LocalItemStruct))
		Destroy();
	else
	{
		ItemInfo.ItemCount = LocalItemStruct.ItemCount;
		PlayerCharacter->GetInteractComponent()->InteractWidget->CantPickUpItem.Broadcast();
	}
}
//-----------------------------------------------------------------------------------------------------------