#include "SubSystem/WorldRuler.h"
#include "SubSystem/EventBus.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Components/AudioComponent.h"
#include "Config/PortalStoneMasterDA.h"
#include "FPS/FPSCharacter.h"
#include "Enemies/EnemyMaster.h"
#include "ActorComponents/Quest/PlayerQuestComponent.h"
#include "Interact/Quest/QuestInteractMaster.h"
#include "Interact/Portal/Portal.h"
#include "Struct/AllDataChance.h"
#include "Struct/ItemTypeChance.h"
#include "Struct/ItemGradeChance.h"
//-----------------------------------------------------------------------------------------------------------
float FPortalStat::GetValueFromSecondChance()
{
	return PortalChanceForSecondChance + ChanceFromPortalStatsCount;
}
//-----------------------------------------------------------------------------------------------------------
float FPortalStat::GetValueFromFailChance()
{
	return PortalChanceForFailChance;
}
//-----------------------------------------------------------------------------------------------------------
bool UWorldRuler::FindQuestTarget(UQuestInteractTargetMasterDA* questTarget, int32& questIndex)
{
	for (int32 i = 0; i < QuestTargets.Num(); i++)
	{
		if (QuestTargets[i] == questTarget)
		{
			questIndex = i;
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::InitDataFromGameMode(UDataTable* DTenemiesData, UDataTable* DTbossesData, UMetaSoundSource* battleSong, const int32 timeCount, const float timeBetweenSpawn, TSoftObjectPtr<UWorld> mainHUB, UDataTable* DTitemTypeChance, UDataTable* DTitemGradeChance, UDataTable* DTitemTypeData, UCurveTable* CTportal)
{
	DTEnemiesData = DTenemiesData;
	DTBossesData = DTbossesData;
	BattleSong = battleSong;
	TimeCount = timeCount;
	TimeBetweenSpawn = timeBetweenSpawn;
	MainHUB = mainHUB;
	DTItemTypeChance = DTitemTypeChance;
	DTItemGradeChance = DTitemGradeChance;
	DTItemTypeData = DTitemTypeData;
	CTPortal = CTportal;

	CurrentTimeCount = TimeCount;
	CurrentSpawnWave = 0;
	bIsBlocking = false;

	UEventBus::OnEnemyDeath.AddUObject(this, &UWorldRuler::EnemyDeath);
}
//-----------------------------------------------------------------------------------------------------------
//Getter
template<typename DataTableClass>
FName UWorldRuler::GetFromChance(UDataTable* dataTable)
{
	if (!dataTable)
	{
		ALARM_LOG
			return FName("Fail");
	}
	DataTableClass* DTRow;
	TArray<FName> rowNames = dataTable->GetRowNames();
	int32 arrayLen = rowNames.Num();
	int32 random;
	TMap<FName, int32> nameCheck;
	do
	{
		do
		{
			if (arrayLen <= nameCheck.Num())
				nameCheck.Empty();

			random = FMath::RandRange(0, arrayLen - 1);
		} while (nameCheck.Find(rowNames[random]));

		nameCheck.Add(rowNames[random], random);

		DTRow = dataTable->FindRow<DataTableClass>(rowNames[random], TEXT(""));
		if (!DTRow)
		{
			ALARM_LOG
				return FName("Fail");
		}
	} while (DTRow->Chance < FMath::FRandRange(0.0, 100.0));

	return rowNames[random];
}
const TSoftObjectPtr<UWorld> UWorldRuler::GetMainHUB()
{
	return MainHUB;
}
const FPortalStat& UWorldRuler::GetPortalStat()
{
	return PortalStat;
}
FVector UWorldRuler::GetDungeonPortalLocation()
{
	return PortalLocation;
}
//-----------------------------------------------------------------------------------------------------------
UDataTable* UWorldRuler::GetChanceTable(EChance chance, EItemGrade portalGrade)
{
	UDataTable* dataTable = nullptr;
	FAllDataChance* dataChance;
	TArray<FName> rowNames;

	switch (chance)
	{
	case Grade:
		dataTable = DTItemGradeChance;
		break;
	case Type:
		dataTable = DTItemTypeChance;
		break;
	default:
		break;
	}

	if (!dataTable)
	{
		ALARM_LOG
			return nullptr;
	}

	rowNames = dataTable->GetRowNames();

	for (FName& item : rowNames)
	{
		dataChance = dataTable->FindRow<FAllDataChance>(item, TEXT(""));
		if (dataChance && dataChance->Grade == portalGrade)
			return dataChance->DataTable;
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------------------------
//Setter
void UWorldRuler::SetPortalStat(UPortalStoneMasterDA* portalDA, int32 itemLevel)
{	
	FItemTypeChance* rowItemTypeDT = nullptr;
	FItemGradeChance* rowItemGradeDT = nullptr;

	ClearPortalStat();

	if (!portalDA)
		return;

	PortalStat.bIsExist = true;
	PortalStat.Level = itemLevel;
	PortalStat.Grade = portalDA->ItemGrade;
	PortalStat.SpawnEnemyWave = portalDA->SpawnEnemyWave;
	PortalStat.SpawnEnemyAmount = portalDA->SpawnEnemyAmount;
	PortalStat.StatsValue.StatsValue = portalDA->StatsValue.StatsValue;
	PortalStat.ItemTypeTable = DTItemTypeData;

	CurrentSpawnEnemyAmount = PortalStat.SpawnEnemyAmount;
	CurrentSpawnWave = 0;
	
	if (CTPortal && PortalStat.Level != 0)
	{
		const FRealCurve* portalLevelCurve1 = CTPortal->FindCurve(FName(TEXT("PortalLevelSecondChance")), TEXT(""));
		if (portalLevelCurve1)
			PortalStat.PortalChanceForSecondChance = portalLevelCurve1->Eval(PortalStat.Level);

		const FRealCurve* portalLevelCurve2 = CTPortal->FindCurve(FName(TEXT("PortalLevelFailChance")), TEXT(""));
		if (portalLevelCurve2)
			PortalStat.PortalChanceForFailChance = portalLevelCurve2->Eval(PortalStat.Level);

		const FRealCurve* portalLevelCurve3 = CTPortal->FindCurve(FName(TEXT("ChanceFromPortalStatsCount")), TEXT(""));
		if (portalLevelCurve3)
			PortalStat.ChanceFromPortalStatsCount = portalLevelCurve3->Eval(PortalStat.StatsValue.StatsValue.Num());
	}

	PortalStat.TypeChanceTable = GetChanceTable(EChance::Type, PortalStat.Grade);
	PortalStat.GradeChanceTable = GetChanceTable(EChance::Grade, PortalStat.Grade);

	CHECK_PTR(PortalStat.TypeChanceTable)
	CHECK_PTR(PortalStat.GradeChanceTable)

	for (const FName& item : PortalStat.TypeChanceTable->GetRowNames())
	{
		rowItemTypeDT = PortalStat.TypeChanceTable->FindRow<FItemTypeChance>(item, TEXT(""));

		switch (rowItemTypeDT->ItemType)
		{
		case ETypeChance::Fail:
			PortalStat.AllTypeChances += rowItemTypeDT->Chance - PortalStat.PortalChanceForFailChance;
			break;
		case ETypeChance::Armor:
		case ETypeChance::Currency:
		case ETypeChance::Magazine:
		case ETypeChance::MagicWeapon:
		case ETypeChance::PortalStone:
		case ETypeChance::Supplies:
			PortalStat.AllTypeChances += rowItemTypeDT->Chance;
			break;
		case ETypeChance::SecondChance:
		default:
			break;
		}
	}

	for (const FName& item : PortalStat.GradeChanceTable->GetRowNames())
	{
		rowItemGradeDT = PortalStat.GradeChanceTable->FindRow<FItemGradeChance>(item, TEXT(""));

		PortalStat.AllGradeChances += rowItemGradeDT->Chance;
	}

}
void UWorldRuler::TESTING_Set_Portal_Stat(int32 portalLevel, EItemGrade portalGrade)
{
	FItemTypeChance* rowItemTypeDT;
	FItemGradeChance* rowItemGradeDT;

	ClearPortalStat();

	PortalStat.bIsExist = true;
	PortalStat.Level = portalLevel;
	PortalStat.Grade = portalGrade;
	PortalStat.ItemTypeTable = DTItemTypeData;

	if (CTPortal && PortalStat.Level != 0)
	{
		const FRealCurve* portalLevelCurve1 = CTPortal->FindCurve(FName(TEXT("PortalLevelSecondChance")), TEXT(""));
		if (portalLevelCurve1)
			PortalStat.PortalChanceForSecondChance = portalLevelCurve1->Eval(PortalStat.Level);

		const FRealCurve* portalLevelCurve2 = CTPortal->FindCurve(FName(TEXT("PortalLevelFailChance")), TEXT(""));
		if (portalLevelCurve2)
			PortalStat.PortalChanceForFailChance = portalLevelCurve2->Eval(PortalStat.Level);

		const FRealCurve* portalLevelCurve3 = CTPortal->FindCurve(FName(TEXT("ChanceFromPortalStatsCount")), TEXT(""));
		if (portalLevelCurve3)
			PortalStat.ChanceFromPortalStatsCount = portalLevelCurve3->Eval(PortalStat.StatsValue.StatsValue.Num());
	}

	PortalStat.TypeChanceTable = GetChanceTable(EChance::Type, PortalStat.Grade);
	PortalStat.GradeChanceTable = GetChanceTable(EChance::Grade, PortalStat.Grade);

	CHECK_PTR(PortalStat.TypeChanceTable)
	CHECK_PTR(PortalStat.GradeChanceTable)

	for (const FName& item : PortalStat.TypeChanceTable->GetRowNames())
	{
		rowItemTypeDT = PortalStat.TypeChanceTable->FindRow<FItemTypeChance>(item, TEXT(""));

		switch (rowItemTypeDT->ItemType)
		{
		case ETypeChance::Fail:
			PortalStat.AllTypeChances += rowItemTypeDT->Chance - PortalStat.PortalChanceForFailChance;
			break;
		case ETypeChance::Armor:
		case ETypeChance::Currency:
		case ETypeChance::Magazine:
		case ETypeChance::MagicWeapon:
		case ETypeChance::PortalStone:
		case ETypeChance::Supplies:
			PortalStat.AllTypeChances += rowItemTypeDT->Chance;
			break;
		case ETypeChance::SecondChance:
		default:
			break;
		}
	}

	for (const FName& item : PortalStat.GradeChanceTable->GetRowNames())
	{
		rowItemGradeDT = PortalStat.GradeChanceTable->FindRow<FItemGradeChance>(item, TEXT(""));

		PortalStat.AllGradeChances += rowItemGradeDT->Chance;
	}

}
//-----------------------------------------------------------------------------------------------------------
bool UWorldRuler::ClearWaveTimeCountTimer()
{
	if (GetWorld()->GetTimerManager().TimerExists(WaveTimeCountTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(WaveTimeCountTimer);
		OnTimeCount.ExecuteIfBound(0);
	}

	if (CurrentSpawnWave >= PortalStat.SpawnEnemyWave)
	{
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, CurrentDungeon, FLatentActionInfo{}, false);
		GetWorld()->GetTimerManager().ClearTimer(TimeToHomeHandle);
		OnTimeCount.ExecuteIfBound(0);

		for (int32 i = AllEnemies.Num() - 1; i >= 0; --i)
		{
			if (AllEnemies[i])
				AllEnemies[i]->Destroy();

			AllEnemies.RemoveAt(i);
		}

		OnWaveCount.ExecuteIfBound(0);

		return false;
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::ResetDungeon()
{
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	TArray<AActor*> illusionsArray = {};

	timerManager.ClearTimer(SpawnTimer);
	timerManager.ClearTimer(SpawnEnemyTimer);
	timerManager.ClearTimer(SpawnSystemTimer);
	timerManager.ClearTimer(WaveTimeCountTimer);

	CurrentTimeCount = TimeCount;
	UGameplayStatics::GetAllActorsWithTag(this, FName("Illusion"), illusionsArray);

	for (AActor* item : illusionsArray)
	{
		if(item)
			item->Destroy();
	}

	for (int32 i = AllEnemies.Num() - 1; i >= 0; i--)
	{
		if (IsValid(AllEnemies[i]))
			AllEnemies[i]->Destroy();

		AllEnemies.RemoveAt(i);
	}

	StopBattleMusic();
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::StartWaveTimeCount()
{
	OnTimeCount.ExecuteIfBound(CurrentTimeCount--);

	if (CurrentTimeCount >= 0)
	{
		StopBattleMusic();
		GetWorld()->GetTimerManager().SetTimer(WaveTimeCountTimer, [&]() { StartWaveTimeCount(); }, 1.0f, false);
	}
	else
	{
		for (int32 i = AllEnemies.Num() - 1; i >= 0; --i)
		{
			if (!IsValid(AllEnemies[i]))
				AllEnemies.RemoveAt(i);
			else
			{
				AllEnemies[i]->EnemyClearing();
				if (!IsValid(AllEnemies[i]))
					AllEnemies.RemoveAt(i);
			}
		}

		FindAndClosePortal();
		SpawnSystem();
		CurrentTimeCount = TimeCount;

		if (BattleSong)
			AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), BattleSong);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::StopBattleMusic()
{
	if (IsValid(AudioComponent))
	{
		AudioComponent->Stop();
		AudioComponent = nullptr;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::FindAndClosePortal()
{
	TArray<AActor*> actors;

	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Portal")), actors);

	for (AActor* item : actors)
	{
		if (IsValid(item))
			item->Destroy();
	}
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::EnemyDeath(UEnemyMasterDA* enemyDataAsset)
{
	CheckAllAliveEnemy();
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::CheckAllAliveEnemy()
{
	int32 aliveEnemies = 0;

	if (AllEnemies.IsEmpty())
		return;

	for (auto item : AllEnemies)
	{
		if (IsValid(item) && !item->bIsDead)
		{
			aliveEnemies++;
			continue;
		}
	}
	
	OnEnemyCount.ExecuteIfBound(aliveEnemies);

	if (aliveEnemies <= 0 && CurrentSpawnEnemyAmount <= 0)
	{
		bIsBlocking = false;
		CurrentSpawnEnemyAmount = PortalStat.SpawnEnemyAmount + 5;

		if (CurrentSpawnWave >= PortalStat.SpawnEnemyWave)
			TimerToHome(60);
		else
			StartWaveTimeCount();
	}
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::SetDungeonPortalLocation(FVector location)
{
	PortalLocation = location;
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::ClearPortalStat()
{
	PortalStat = {};
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::TriggerOnPortalSpawn(const FVector& location)
{
	PortalLocation = location;

	OnPortalSpawn.Broadcast();

	//TODO : ѕоиск\удаление квестовых ништ€ков
	bool bHasQuest = false;
	AQuestInteractMaster* questInteract = nullptr;
	UPlayerQuestComponent* questComponent = nullptr;
	TArray<AActor*> questInteractArray = {};
	TArray<int32> indexes = {};
	CHECK_CAST(PlayerCharacter, AFPSCharacter, UGameplayStatics::GetPlayerCharacter(this, 0))

	questComponent = PlayerCharacter->GetQuestComponent();
	CHECK_PTR(questComponent)

		UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("QuestInteract")), questInteractArray);
	for (AActor* item : questInteractArray)
	{
		questInteract = Cast<AQuestInteractMaster>(item);
		if (!questInteract)
			continue;

		bHasQuest = questComponent->FindQuestsByTarget(questInteract->QuestInteractDA, indexes);
		if (!bHasQuest)
			questInteract->Destroy();
	}
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::SpawnSystem()
{
	bIsBlocking = true;

	CurrentSpawnWave++;

	OnWaveCount.ExecuteIfBound(CurrentSpawnWave);


	if (CurrentSpawnWave == PortalStat.SpawnEnemyWave)
	{
		FindLocationForSpawnAndSpawn(false); // Boss Spawn!!!
		GetWorld()->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &UWorldRuler::SpawnEnemy, TimeBetweenSpawn, false);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &UWorldRuler::SpawnEnemy, TimeBetweenSpawn, false);
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::SpawnEnemy()
{
	int32 enemyCount = 0;

	if (CurrentSpawnEnemyAmount <= 0)
		return;

	FindLocationForSpawnAndSpawn(true);

	for (AEnemyMaster* item : AllEnemies)
	{
		if (!IsValid(item))
			continue;

		if (!item->bIsDead)
			++enemyCount;
	}
	GetWorld()->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &UWorldRuler::SpawnEnemy, TimeBetweenSpawn + (enemyCount / 5), false);
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::FindLocationForSpawnAndSpawn(bool bIsEnemySpawn)
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, bIsEnemySpawn]()
		{
			bool bIsTouch;

			bool temp1;
			bool temp2;
			bool temp3;

			int32 aliveEnemies = 0;
			int32 spawnEnemyAmount = 1;
			int32 infinityBlock = 0;
			float spawnRadius = 7575.0f;

			UNavigationSystemV1* navSys;
			ANavigationData* useNavData;
			FEnemiesData* enemyData;

			FHitResult hitResult = {};
			FVector spawnCenterLocation = {};
			FVector randomPoint = {};
			FNavLocation navRandomPoint(spawnCenterLocation);
			FPathFindingQuery query = {};
			FName enemyName = {};
			FEnemySpawn enemySpawn = {};
			TArray<AActor*> sphereTraceIgnore = {};

			/*bool bIsLineTraceTouch = false;*/
			/*FHitResult LocalLineTraceHitResult = {};*/
			/*TArray<AActor*> LocalLineTraceIgnore = {};*/

			CHECK_CAST(PlayerCharacter, AFPSCharacter, UGameplayStatics::GetPlayerCharacter(this, 0))

			for (AEnemyMaster* item : AllEnemies)
			{
				if (IsValid(item) && !item->bIsDead)
				{
					aliveEnemies++;
					continue;
				}
			}
			if (aliveEnemies >= 18)
				return;

			infinityBlock = 3500;
			spawnCenterLocation = PlayerCharacter->GetActorLocation();
			sphereTraceIgnore.Add(PlayerCharacter);

			do
			{
				if (infinityBlock <= 0)
					break;

				navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(PlayerCharacter->GetWorld());
				if (!navSys)
				{
					ALARM_LOG
						break;
				}

				useNavData = navSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
				if (!useNavData)
				{
					ALARM_LOG
						break;
				}

				navSys->GetRandomReachablePointInRadius(spawnCenterLocation, spawnRadius, navRandomPoint, useNavData,
					UNavigationQueryFilter::GetQueryFilter(*useNavData, PlayerCharacter->GetWorld(), UNavigationQueryFilter::StaticClass()));
				randomPoint = navRandomPoint.Location + FVector(0.0, 0.0, 65.0); //TODO : ѕересмотреть положение

				bIsTouch = UKismetSystemLibrary::SphereTraceSingle(PlayerCharacter->GetWorld(), randomPoint + FVector(0.0, 0.0, 90.0), randomPoint + FVector(0.0, 0.0, 200.0), 60.0,
					ETraceTypeQuery::TraceTypeQuery1, false, sphereTraceIgnore, EDrawDebugTrace::None, hitResult, true);

				//“рейс от точки спавна к игроку что бы не спавнилс€ в зоне видимости игрока
				/*bIsLineTraceTouch = UKismetSystemLibrary::LineTraceSingle(PlayerCharacter->GetWorld(), LocalRandomPoint, PlayerCharacter->GetActorLocation(), ETraceTypeQuery::TraceTypeQuery1,
					false, LocalLineTraceIgnore, EDrawDebugTrace::None, LocalLineTraceHitResult, true);*/

					//ѕроверка найден ли путь между местом спавна и игроком`
				query.StartLocation = randomPoint;
				query.EndLocation = spawnCenterLocation;
				query.NavData = useNavData;

				CHECK_PTR(DTEnemiesData)
				CHECK_PTR(DTBossesData)

				if (bIsEnemySpawn)
				{
					enemyName = GetFromChance<FEnemiesData>(DTEnemiesData);
					enemyData = DTEnemiesData->FindRow<FEnemiesData>(enemyName, "");
				}
				else
				{
					enemyName = GetFromChance<FEnemiesData>(DTBossesData);
					enemyData = DTBossesData->FindRow<FEnemiesData>(enemyName, "");
				}

				temp1 = FVector::Distance(randomPoint, spawnCenterLocation) <= 1050.0f;
				temp2 = !navSys->TestPathSync(query);
				temp3 = enemyName == FName("Fail");
				//ѕроверка от точки спавна к игроку что бы не спавнилс€ в зоне видимости игрока
				/*LocalTemp5 = LocalLineTraceHitResult.GetActor() ? LocalLineTraceHitResult.GetActor()->ActorHasTag(FName(TEXT("Player"))) : true;*/

				if (bIsTouch || temp1 || temp2 || temp3 || !enemyData)
				{
					--infinityBlock;
					continue;
				}

				enemySpawn.EnemyDataRow = enemyData;
				enemySpawn.SpawnPoint = randomPoint;
				EnemySpawnArray.Add(enemySpawn);

				--spawnEnemyAmount;
			} while (spawnEnemyAmount > 0);

			AsyncTask(ENamedThreads::GameThread, [this, spawnEnemyAmount, bIsEnemySpawn]()
				{
					if (spawnEnemyAmount > 0)
					{
						FindLocationForSpawnAndSpawn(bIsEnemySpawn);
						return;
					}

					GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &UWorldRuler::Spawn, 0.27, true);
				});
		});
}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::TimerToHome(const int32 time)
{
	CurrentTimeCount = time;

	int32 timeCount = --CurrentTimeCount;

	OnTimeCount.ExecuteIfBound(timeCount);
	if (timeCount == 10)
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, MainHUB, true, false, FLatentActionInfo{});

	if (timeCount <= 0)
	{
		APortal* portal = nullptr;
		TArray<AActor*> actors = {};
		UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("PortalAltar")), actors);
		ResetDungeon();

		CHECK_PTR(actors[0])

			portal = Cast<APortal>(actors[0]);

		CHECK_PTR(portal)
			CHECK_PTR(portal->ArrowComponent)
			CHECK_CAST(PlayerCharacter, AFPSCharacter, UGameplayStatics::GetPlayerCharacter(this, 0))

			actors.Empty();
		UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Level_DIrectional_Light")), actors);
		for (AActor* item : actors)
		{
			if (item)
				item->SetActorHiddenInGame(true);
		}

		PlayerCharacter->SetActorLocation(portal->ArrowComponent->GetComponentLocation());
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, CurrentDungeon, FLatentActionInfo{}, false);

		OnEnemyCount.ExecuteIfBound(0);
		OnWaveCount.ExecuteIfBound(0);
		CurrentTimeCount = TimeCount;

		if (AudioComponent)
		{
			AudioComponent->Stop();
			AudioComponent = nullptr;
		}

		return;
	}

	GetWorld()->GetTimerManager().SetTimer(TimeToHomeHandle, [this, timeCount]() { TimerToHome(timeCount); }, 1.0, false);

}
//-----------------------------------------------------------------------------------------------------------
void UWorldRuler::Spawn()
{
	if (EnemySpawnArray.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
		return;
	}

	AEnemyMaster* enemy = nullptr;
	FEnemySpawn enemySpawn = EnemySpawnArray[EnemySpawnArray.Num() - 1];
	TSoftObjectPtr<UCharacterMasterDA> enemyDA;

	if (!enemySpawn.EnemyDataRow->EnemyData.Contains(PortalStat.Grade))
	{
		ALARM_LOG
			return;
	}

	enemyDA = *enemySpawn.EnemyDataRow->EnemyData.Find(PortalStat.Grade);

	if (!enemyDA.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(enemyDA.ToSoftObjectPath(), [this]()
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						Spawn();
					});
			});
		return;
	}

	if (!enemySpawn.EnemyDataRow->Enemy.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(enemySpawn.EnemyDataRow->Enemy.ToSoftObjectPath(), [this]()
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						Spawn();
					});

			});
		return;
	}

	FActorSpawnParameters spawnParams;
	EnemySpawnArray.RemoveAt(EnemySpawnArray.Num() - 1);
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	enemy = GetWorld()->SpawnActor<AEnemyMaster>(enemySpawn.EnemyDataRow->Enemy.Get(), enemySpawn.SpawnPoint, FRotator{}, spawnParams);
	CHECK_PTR(enemy)

	CurrentSpawnEnemyAmount--;
	enemy->SetDataAsset(enemyDA.Get());
	AllEnemies.Add(enemy);
	enemy->InitEnemy(PortalStat, PlayerCharacter);

	CheckAllAliveEnemy();
}

