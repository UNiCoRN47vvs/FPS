#include "Interact/Chest/TreasureChest.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/WorldRuler.h"
#include "FPS/FPSGameMode.h"
#include "Character/CharacterMaster.h"
#include "ActorComponents/Chest/ChestComponent.h"
#include "ActorComponents/Drop/DropComponent.h"
//-----------------------------------------------------------------------------------------------------------
ATreasureChest::ATreasureChest()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	
	StaticMeshComponent->SetupAttachment(ItemScene);
}
//-----------------------------------------------------------------------------------------------------------
void ATreasureChest::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	UWorldRuler* worldRuler = nullptr;
	UDropComponent* dropComponent = nullptr;
	int32 count = 0;
	float random = 0.0;

	random = FMath::RandRange(0.0f, 100.0f);
	if (random >= 33.0f) //TODO : Перенести значение 35.0 в переменную
	{
		Destroy();
		return;
	}

	CHECK_PTR(world)

	worldRuler = world->GetSubsystem<UWorldRuler>();
	CHECK_PTR(worldRuler)

	count = static_cast<int32>(worldRuler->GetPortalStat().Grade) + 1;
	
	dropComponent = FindComponentByClass<UDropComponent>();
	CHECK_PTR(dropComponent)

	for (int32 i = 0; i < count; ++i)
	{
		dropComponent->SearchDrop(DTSpecialDrop);
	}
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct ATreasureChest::GetInteractInfo()
{
	return InteractInfo;
}
//-----------------------------------------------------------------------------------------------------------
void ATreasureChest::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	CHECK_PTR(PlayerCharacter)

	UDropComponent* dropComponent = nullptr;
	UChestComponent* chestComponent = FindComponentByClass<UChestComponent>();
	CHECK_PTR(chestComponent)

	PlayerCharacter->ApplyInteract(EStorageType::TreasureInventory, chestComponent);
	UGameplayStatics::PlaySound2D(this, OpenSound);

	dropComponent = FindComponentByClass<UDropComponent>();
	CHECK_PTR(dropComponent)

	dropComponent->Deactivate();
	dropComponent->DestroyComponent();

}
//-----------------------------------------------------------------------------------------------------------
void ATreasureChest::ApplyDrop(FItemInvStruct& Item, UNiagaraSystem* Niagara, FLinearColor Color)
{
	UChestComponent* chestComponent = FindComponentByClass<UChestComponent>();
	CHECK_PTR(chestComponent)

	chestComponent->PickUpItem(Item.ItemCount, Item.ItemDA, 0, Item.StatValue);
}
//-----------------------------------------------------------------------------------------------------------
void ATreasureChest::DeleteEnemyComponents()
{

}
//-----------------------------------------------------------------------------------------------------------