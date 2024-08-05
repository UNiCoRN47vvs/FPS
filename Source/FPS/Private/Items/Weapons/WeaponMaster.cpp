#include "Items/Weapons/WeaponMaster.h"
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