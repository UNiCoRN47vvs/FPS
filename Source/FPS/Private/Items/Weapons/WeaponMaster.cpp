#include "Items/Weapons/WeaponMaster.h"
//-----------------------------------------------------------------------------------------------------------
AWeaponMaster::AWeaponMaster()
{
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));

	SkeletalMeshComponent->SetupAttachment(ItemScene);
	ItemSphereComponent->SetupAttachment(SkeletalMeshComponent);
}
