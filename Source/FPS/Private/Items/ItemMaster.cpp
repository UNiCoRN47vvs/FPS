#include "Items/ItemMaster.h"
#include "Interfaces/PlayerInteract.h"
//-----------------------------------------------------------------------------------------------------------
AItemMaster::AItemMaster()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemScene = CreateDefaultSubobject<USceneComponent>(TEXT("Item Scene Component"));
	ItemSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Item Sphere Component"));

	ItemScene->SetupAttachment(RootComponent);

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

	if (!PlayerInterface)
	{
		PlayerInterface = Cast<IPlayerInteract>(OtherActor);
		if (!PlayerInterface)
		{
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, PlayerInterface = nullptr!")));
			return;
		}
	}

	PlayerInterface->InteractPlayerWithItem(true);
	
}
void AItemMaster::OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherActor->GetClass()->ImplementsInterface(UPlayerInteract::StaticClass()))
		return;

	if (!PlayerInterface)
	{
		PlayerInterface = Cast<IPlayerInteract>(OtherActor);
		if (!PlayerInterface)
		{
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, PlayerInterface = nullptr!")));
			return;
		}
	}

	PlayerInterface->InteractPlayerWithItem(false);
}
//-----------------------------------------------------------------------------------------------------------
//Getter
FItemStructMaster AItemMaster::GetItemInfo()
{
	return ItemInfo;
}
//-----------------------------------------------------------------------------------------------------------
void AItemMaster::InteractWithActor(AFPSCharacter* PlayerCharacter)
{
	if (PlayerInterface)
	{
	}
	else
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, PlayerInterface = nullptr!")));

	Destroy();
}
//-----------------------------------------------------------------------------------------------------------