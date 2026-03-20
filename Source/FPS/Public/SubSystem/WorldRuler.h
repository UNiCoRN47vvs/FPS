#pragma once

#include "FPS/FPS.h"
#include "Subsystems/WorldSubsystem.h"
#include "Enums/ItemGrade.h"
#include "Struct/StatValueStruct.h"
#include "WorldRuler.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UQuestInteractTargetMasterDA;
class AEnemyMaster;
class UMetaSoundSource;
class UEnemyMasterDA;
class UPortalStoneMasterDA;
class AFPSCharacter;
struct FEnemiesData;
//-----------------------------------------------------------------------------------------------------------
enum EChance
{
	Grade,
	Type
};
//-----------------------------------------------------------------------------------------------------------
struct FEnemySpawn
{
	FEnemiesData* EnemyDataRow = nullptr;
	FVector SpawnPoint = {};
};
//-----------------------------------------------------------------------------------------------------------
USTRUCT()
struct FPortalStat
{
	GENERATED_BODY()
	float GetValueFromSecondChance();
	float GetValueFromFailChance();

	UPROPERTY() uint8 bIsExist : 1 = false;
	UPROPERTY() int32 Level = 0;
	UPROPERTY() int32 SpawnEnemyAmount = 0;
	UPROPERTY() int32 SpawnEnemyWave = 0;
	UPROPERTY() EItemGrade Grade = EItemGrade::White;
	UPROPERTY() float PortalChanceForSecondChance = 0.0f;
	UPROPERTY() float PortalChanceForFailChance = 0.0f;
	UPROPERTY() float ChanceFromPortalStatsCount = 0.0f;
	UPROPERTY() float AllTypeChances = 0.0f;
	UPROPERTY() float AllGradeChances = 0.0f;
	UPROPERTY() UDataTable* TypeChanceTable = nullptr;
	UPROPERTY() UDataTable* GradeChanceTable = nullptr;
	UPROPERTY() UDataTable* ItemTypeTable = nullptr;
	UPROPERTY() FStatValueStruct StatsValue = {};
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UWorldRuler : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	void InitDataFromGameMode(UDataTable* DTenemiesData, UDataTable* DTbossesData, UMetaSoundSource* battleSong, const int32 timeCount, const float timeBetweenSpawn, TSoftObjectPtr<UWorld> mainHUB, UDataTable* DTitemTypeChance, UDataTable* DTitemGradeChance, UDataTable* DTitemTypeData, UCurveTable* CTportal);
	
	const TSoftObjectPtr<UWorld> GetMainHUB();
	const FPortalStat& GetPortalStat();
	FVector GetDungeonPortalLocation();

	void SetPortalStat(UPortalStoneMasterDA* portalDA, int32 itemLevel);
	void TESTING_Set_Portal_Stat(int32 portalLevel, EItemGrade portalGrade);
	void SetDungeonPortalLocation(FVector location);

	void ClearPortalStat();
	void ResetDungeon();
	void TriggerOnPortalSpawn(const FVector& location);

	void TimerToHome(const int32 time);
	void StopBattleMusic();
	void StartWaveTimeCount();
	bool ClearWaveTimeCountTimer();
	bool FindQuestTarget(UQuestInteractTargetMasterDA* questTarget, int32& questIndex);
	UPROPERTY() uint8 bIsBlocking : 1;
	UPROPERTY() TArray<UQuestInteractTargetMasterDA*> QuestTargets;
	UPROPERTY() TSoftObjectPtr<UWorld> CurrentDungeon;

	TMulticastDelegate<void()> OnPortalSpawn;
	TDelegate<void(int32)> OnTimeCount;
	TDelegate<void(int32)> OnWaveCount;
	TDelegate<void(int32)> OnEnemyCount;
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY() int32 TimeCount;
	UPROPERTY() UDataTable* DTEnemiesData;
	UPROPERTY() UDataTable* DTBossesData;
	UPROPERTY() UDataTable* DTItemTypeChance;
	UPROPERTY() UDataTable* DTItemGradeChance;
	UPROPERTY() UDataTable* DTItemTypeData;
	UPROPERTY() UCurveTable* CTPortal;
	UPROPERTY() UMetaSoundSource* BattleSong;
	UPROPERTY() UAudioComponent* AudioComponent;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() TSoftObjectPtr<UWorld> MainHUB;
	UPROPERTY() float TimeBetweenSpawn;
	UPROPERTY() FPortalStat PortalStat;
	UPROPERTY() FTimerHandle SpawnTimer;
	UPROPERTY() FTimerHandle SpawnEnemyTimer;
	UPROPERTY() FTimerHandle SpawnSystemTimer;
	UPROPERTY() FTimerHandle WaveTimeCountTimer;
	UPROPERTY() FTimerHandle TimeToHomeHandle;
	UPROPERTY() TArray<AEnemyMaster*> AllEnemies;
	int32 CurrentSpawnEnemyAmount;
	int32 CurrentSpawnWave;
	int32 CurrentTimeCount;
	FVector PortalLocation;
	TArray<FEnemySpawn> EnemySpawnArray;

private:
	UFUNCTION() void EnemyDeath(UEnemyMasterDA* enemyDataAsset);
	template<typename DataTableClass> FName GetFromChance(UDataTable* dataTable);
	UDataTable* GetChanceTable(EChance chance, EItemGrade portalGrade);
	void FindAndClosePortal();
	void SpawnSystem();
	void FindLocationForSpawnAndSpawn(bool bIsEnemySpawn);
	void SpawnEnemy();
	void Spawn();
	void CheckAllAliveEnemy();
};
//-----------------------------------------------------------------------------------------------------------