#include "Items/ItemMaster.h"
#include "Interfaces/PlayerInteract.h"
//-----------------------------------------------------------------------------------------------------------
AItemMaster::AItemMaster()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemScene = CreateDefaultSubobject<USceneComponent>(TEXT("Item Scene Component"));
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Statick Mesh Component"));
	ItemSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Item Sphere Component"));

	ItemScene->SetupAttachment(RootComponent);
	ItemStaticMesh->SetupAttachment(ItemScene);
	ItemSphereComponent->SetupAttachment(ItemStaticMesh);

	ItemSphereComponent->InitSphereRadius(170.0);
}
//-----------------------------------------------------------------------------------------------------------
void AItemMaster::BeginPlay()
{
	ItemSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemMaster::OnOverlapBegin);
	ItemSphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItemMaster::OnOverlapEnd);
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
//ItemSphereComponent Overlaping
void AItemMaster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
		return;

	IPlayerInteract* LocalPlayerInterface = Cast<IPlayerInteract>(OtherActor);
	if (LocalPlayerInterface)
	{
		LocalPlayerInterface->InteractPlayerWithItem(true);
	}
}
void AItemMaster::OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherActor->Implements<IPlayerInteract>())
		return;

	IPlayerInteract* LocalPlayerInterface = Cast<IPlayerInteract>(OtherActor);
	if (LocalPlayerInterface)
	{
		LocalPlayerInterface->InteractPlayerWithItem(false);
	}
}
//-----------------------------------------------------------------------------------------------------------
//Getter
FString AItemMaster::GetItemInfo()
{
	return TestString;
}
