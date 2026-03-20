#include "Config/HomePortalMasterDA.h"
#include "GameFramework/Character.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/WorldRuler.h"
#include "FPS/FPSPlayerController.h"
#include "Interact/Portal/EnterPortal.h"
//-----------------------------------------------------------------------------------------------------------
bool UHomePortalMasterDA::UseItem(AFPSPlayerController* playerController)
{
	if (!playerController || ItemType == EItemType::PortalStone && (playerController->bIsHome || playerController->SpawnSystemIsBlocking()))
		return false;

	FLatentActionInfo latentInfo = {};
	UWorldRuler* worldRuler = playerController->GetWorld()->GetSubsystem<UWorldRuler>();
	TArray<AActor*> tagActors = {};
	if (!worldRuler)
	{
		ALARM_LOG
		return false;
	}

	PlayerController = playerController;
	latentInfo.CallbackTarget = this;
	latentInfo.ExecutionFunction = FName("HUBLoaded");
	latentInfo.Linkage = 0;
	latentInfo.UUID = __LINE__;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(playerController, worldRuler->GetMainHUB(), true, false, latentInfo);
	UGameplayStatics::GetAllActorsWithTag(playerController, FName(TEXT("Portal")), tagActors);

	playerController->CreateWidgetInMainHUD(EStorageType::Inventory);

	if (tagActors.IsEmpty())
		return false;

	for (AActor* item : tagActors)
	{
		if (item)
			item->Destroy();
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UHomePortalMasterDA::HUBLoaded()
{
	if (!EnterPortal.ToSoftObjectPath().ResolveObject())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(EnterPortal.ToSoftObjectPath(), [this]()
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						HUBLoaded();
					});
			});
		return;
	}

	bool bIsTouch = false;
	bool bLineTraceIsTouch = false;
	int32 infinityBlock = 100;
	double spawnRadius = 1000.0;
	FVector spawnCenterLocation = {};
	FVector randomPoint = {};
	FVector playerLocation = {};
	FHitResult hitResult = {};
	FHitResult lineTraceHitResult = {};
	FTimerHandle timer;
	FNavLocation point(spawnCenterLocation);
	FPathFindingQuery query;
	FActorSpawnParameters spawnParams = {};
	AEnterPortal* enterPortal = nullptr;
	UNavigationSystemV1* navSys = nullptr;
	ANavigationData* useNavData = nullptr;
	TArray<AActor*> characters = {};
	TArray<AActor*> lineTraceIgnore = {};

	CHECK_PTR(PlayerController)
	spawnCenterLocation = PlayerController->GetPawn()->GetActorLocation();

	navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(PlayerController);
	CHECK_PTR(navSys)

	playerLocation = PlayerController->GetCharacter()->GetActorLocation();
	lineTraceIgnore.Add(PlayerController->GetCharacter());
	do
	{
		useNavData = navSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
		CHECK_PTR(useNavData)

		navSys->GetRandomReachablePointInRadius(spawnCenterLocation, spawnRadius, point, useNavData,
			UNavigationQueryFilter::GetQueryFilter(*useNavData, PlayerController->GetWorld(), UNavigationQueryFilter::StaticClass()));

		randomPoint = point.Location + FVector(0.0, 0.0, 85.0);

		bIsTouch = UKismetSystemLibrary::SphereTraceSingle(PlayerController, randomPoint, randomPoint + FVector(0.0, 0.0, 190.0), 80.0,
			ETraceTypeQuery::TraceTypeQuery1, false, characters, EDrawDebugTrace::None, hitResult, true);

		bLineTraceIsTouch = UKismetSystemLibrary::LineTraceSingle(PlayerController, randomPoint, playerLocation, ETraceTypeQuery::TraceTypeQuery1, false,
			lineTraceIgnore, EDrawDebugTrace::None, lineTraceHitResult, true);

		if (bIsTouch || bLineTraceIsTouch || FVector::Distance(randomPoint, spawnCenterLocation) <= 300.0)
		{
			--infinityBlock;
			continue;
		}

		query.StartLocation = randomPoint;
		query.EndLocation = spawnCenterLocation;
		query.NavData = useNavData;
		if (navSys->TestPathSync(query))
			break;

		--infinityBlock;
	} while (infinityBlock >= 0);

	if (infinityBlock <= 0)
	{
		PlayerController->GetWorld()->GetTimerManager().SetTimer(timer, [&]() {HUBLoaded(); }, 0.6, false);
		return;
	}

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	enterPortal = PlayerController->GetWorld()->SpawnActor<AEnterPortal>(EnterPortal.Get(), randomPoint, PlayerController->GetPawn()->GetActorRotation(), spawnParams);
	CHECK_PTR(enterPortal)

	enterPortal->SetActorLocation(randomPoint);
	enterPortal->InitEnterPortal(EPortalDestination::Home);
}
//-----------------------------------------------------------------------------------------------------------