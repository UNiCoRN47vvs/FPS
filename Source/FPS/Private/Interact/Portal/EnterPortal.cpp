#include "Interact/Portal/EnterPortal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "SubSystem/WorldRuler.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
#include "NiagaraComponent.h"
#include "NavigationSystem.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Interact/Portal/Portal.h"
//-----------------------------------------------------------------------------------------------------------
AEnterPortal::AEnterPortal()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	
	RootComponent = SceneComponent;
	NiagaraComponent->SetupAttachment(SceneComponent);
	BoxComponent->SetupAttachment(SceneComponent);
	Tags.Add(FName(TEXT("Portal")));
}
//-----------------------------------------------------------------------------------------------------------
void AEnterPortal::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void AEnterPortal::InitEnterPortal(EPortalDestination destinationPortal)
{
	APortal* portalAltar = nullptr;
	TArray<AActor*> portalAltars = {};
	FName portalName = {};
	PortalDestination = destinationPortal;

	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	switch (PortalDestination)
	{
	case Home:
	{
		portalName = TEXT("PortalAltar");
		UGameplayStatics::GetAllActorsWithTag(this, portalName, portalAltars);
		if (portalAltars.IsEmpty())
		{
			ALARM_LOG
			return;
		}
		portalAltar = Cast<APortal>(portalAltars[0]);
		CHECK_PTR(portalAltar)
		WorldRuler->SetDungeonPortalLocation(portalAltar->ArrowComponent->GetComponentLocation());

		break;
	}
	case Dungeon:
		//TODO : Узнавать открыт ли уже наш данж !!!
		
		break;
	}

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnterPortal::OnOverlapBegin);
}
//-----------------------------------------------------------------------------------------------------------
void AEnterPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherComp->ComponentHasTag(FName(TEXT("Player"))))
		return;

	UNavigationSystemV1* navSys = nullptr;
	APortal* portal = nullptr;
	APawn* pawn = nullptr;
	AFPSPlayerController* playerController = nullptr;
	FLatentActionInfo latentInfo;
	TArray<AActor*> arrayActors = {};

	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("PortalAltar")), arrayActors);

	if (!arrayActors.IsValidIndex(0))
		return;

	CHECK_PTR(arrayActors[0])

	portal = Cast<APortal>(arrayActors[0]);

	CHECK_PTR(portal);

	/*arrayActors.Empty();
	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Level_DIrectional_Light")), arrayActors);*/

	pawn = Cast<APawn>(OtherActor);
	CHECK_PTR(pawn)

	playerController = Cast<AFPSPlayerController>(pawn->GetController());
	CHECK_PTR(playerController)

	UEventBus::OnSaveGame.ExecuteIfBound();

	switch (PortalDestination)
	{
	case Home:
		/*for (auto* item : arrayActors)
		{
			if(item)
				item->SetActorHiddenInGame(true);
		}*/

		if(WorldRuler->ClearWaveTimeCountTimer() )
			portal->ActivatePortalSpawnCollision();

		OtherActor->SetActorLocation(WorldRuler->GetDungeonPortalLocation(), false, nullptr, ETeleportType::TeleportPhysics);
		WorldRuler->SetDungeonPortalLocation(GetActorLocation());
		WorldRuler->StopBattleMusic();

		playerController->bIsHome = true;
		this->Destroy();
		break;
	case Dungeon:

		/*for (auto* item : arrayActors)
		{
			if (item)
				item->SetActorHiddenInGame(false);
		}*/

		latentInfo.CallbackTarget = this;
		latentInfo.ExecutionFunction = FName("UnloadTrigger");
		latentInfo.Linkage = 0;
		latentInfo.UUID = __LINE__;
			
		playerController->bIsHome = false;
		playerController->SetWaveTimeCount();
		WorldRuler->StartWaveTimeCount();

		BoxComponent->Deactivate();
		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		OtherActor->SetActorLocation(WorldRuler->GetDungeonPortalLocation(), false, nullptr, ETeleportType::TeleportPhysics);
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(OtherActor, WorldRuler->GetMainHUB(), latentInfo, false);
		break;
	default:
		break;
	}

}
//-----------------------------------------------------------------------------------------------------------
void AEnterPortal::UnloadTrigger()
{
	this->Destroy();
}
//-----------------------------------------------------------------------------------------------------------
void AEnterPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

