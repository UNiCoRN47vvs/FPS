#include "Items/Weapons/WeaponMaster.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
//-----------------------------------------------------------------------------------------------------------
AWeaponMaster::AWeaponMaster()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SkeletalMeshComponent->SetupAttachment(ItemScene);
	ItemSphereComponent->SetupAttachment(SkeletalMeshComponent);

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMesh* LocalSkeletalMesh = ItemWeaponInfo.SkeletalMesh.LoadSynchronous();
	if (LocalSkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(LocalSkeletalMesh);
		SkeletalMeshComponent->SetSimulatePhysics(true);
	}
}
//-----------------------------------------------------------------------------------------------------------
void AWeaponMaster::InteractWithActor(AFPSCharacter* PlayerCharacter)
{
	Super::InteractWithActor(PlayerCharacter);
	if (!PlayerCharacter)
		return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, PlayerInterface = nullptr!")));

	FItemInvStruct LocalItemStruct;
	LocalItemStruct.ItemValue    = ItemWeaponInfo.Damage;
	LocalItemStruct.ItemCount    = ItemInfo.ItemCount;
	LocalItemStruct.ItemCountMax = ItemInfo.ItemCountMax;
	LocalItemStruct.ItemName     = ItemInfo.ItemName;
	LocalItemStruct.ItemDesc     = ItemInfo.ItemDesc;
	LocalItemStruct.ItemIcon     = ItemInfo.ItemIcon;
	LocalItemStruct.ItemClass    = ItemInfo.ItemClass;

	if (PlayerCharacter->GetInventoryComponent()->PickUpItem(LocalItemStruct))
		Destroy();
	else
		ItemInfo.ItemCount = LocalItemStruct.ItemCount;

}