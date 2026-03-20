#include "Interact/Portal/Portal.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Components/ArrowComponent.h"
#include "SubSystem/WorldRuler.h"
#include "FPS/FPSGameMode.h"
#include "Character/CharacterMaster.h"
#include "FPS/FPSPlayerController.h"
#include "ActorComponents/Portal/PortalComponent.h"
#include "Interact/Portal/EnterPortal.h"
//-----------------------------------------------------------------------------------------------------------
APortal::APortal()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	StandStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand Static Mesh Component"));
	SpotStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot Static Mesh Component"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	BackPortalSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Back Portal Sphere Component"));

	RootComponent = SceneComponent;
	StandStaticMeshComponent->SetupAttachment(SceneComponent);

	SpotStaticMeshComponent->SetupAttachment(SceneComponent);
	BackPortalSphereComponent->SetupAttachment(SpotStaticMeshComponent);
	ArrowComponent->SetupAttachment(SpotStaticMeshComponent);

	Tags.Add(TEXT("PortalAltar"));
}
//-----------------------------------------------------------------------------------------------------------
void APortal::InteractWithActor(ACharacterMaster* PlayerCharacter)
{
	CHECK_PTR(PlayerCharacter)

	PlayerCharacter->ApplyInteract(EStorageType::Portal, GetPortalComponent());
}
//-----------------------------------------------------------------------------------------------------------
//Getters
FInteractStruct APortal::GetInteractInfo()
{
	return InteractInfo;
}
UPortalComponent* APortal::GetPortalComponent()
{
	if (!PortalComponent)
		PortalComponent = FindComponentByClass<UPortalComponent>();

	return PortalComponent;
}
//-----------------------------------------------------------------------------------------------------------
void APortal::BeginPlay()
{
	Super::BeginPlay();
	//BackPortalSphereComponent->OnComponentEndOverlap.AddDynamic(this, APortal::OnChildOverlapEnd);
	BackPortalSphereComponent->Deactivate();
	BackPortalSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}
//-----------------------------------------------------------------------------------------------------------
void APortal::OpenPortal(AFPSPlayerController* playerController, TSoftObjectPtr<UWorld> portalLevel, EItemGrade itemGrade)
{
	CHECK_PTR(playerController)

	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	playerController->CreateWidgetInMainHUD(EStorageType::Inventory);

	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, portalLevel, true, false, FLatentActionInfo{});

	WorldRuler->OnPortalSpawn.RemoveAll(this);
	WorldRuler->CurrentDungeon = portalLevel;
	WorldRuler->OnPortalSpawn.AddUObject(this, &APortal::SpawnEnterPortal);
}
//-----------------------------------------------------------------------------------------------------------
void APortal::ActivatePortalSpawnCollision()
{
	BackPortalSphereComponent->Activate(true);
	BackPortalSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
//-----------------------------------------------------------------------------------------------------------
void APortal::OnChildOverlapEnd()
{
	
	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	if (!WorldRuler->GetPortalStat().bIsExist)
		return;

	SpawnEnterPortal();

	BackPortalSphereComponent->Deactivate();
	BackPortalSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}
//-----------------------------------------------------------------------------------------------------------
void APortal::SpawnEnterPortal()
{
	if (IsValid(EnterPortal))
	{
		EnterPortal->Destroy();
		EnterPortal = nullptr;
	}

	if (!EnterPortalClass.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(EnterPortalClass.ToSoftObjectPath(), [this]() 
			{
				if (EnterPortalClass.LoadSynchronous())
				{
					AsyncTask(ENamedThreads::GameThread, [this]() 
						{
							SpawnEnterPortal();
						});
				}
			});
		return;
	}

	CHECK_PTR(EnterPortalClass)
	CHECK_PTR(ArrowComponent)

	FActorSpawnParameters spawnParams = {};
	FVector arrowLocation = ArrowComponent->GetComponentLocation();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//TODO : —делать глобальным и сделать метод дл€ удалени€.
	EnterPortal = GetWorld()->SpawnActor<AEnterPortal>(EnterPortalClass.Get(), arrowLocation, ArrowComponent->GetComponentRotation(), spawnParams);
	CHECK_PTR(EnterPortal)

	EnterPortal->SetActorLocation(arrowLocation);
	EnterPortal->InitEnterPortal(EPortalDestination::Dungeon);
}
//-----------------------------------------------------------------------------------------------------------