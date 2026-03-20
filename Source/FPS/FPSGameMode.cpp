#include "FPSGameMode.h"
#include "SubSystem/WorldRuler.h"
#include "UObject/ConstructorHelpers.h"
//-----------------------------------------------------------------------------------------------------------
AFPSGameMode::AFPSGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
//-----------------------------------------------------------------------------------------------------------
void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
	CHECK_PTR(WorldRuler)

	WorldRuler->InitDataFromGameMode(DTEnemiesData, DTBossesData, BattleSong, TimeCount, TimeBetweenSpawn, MainHUB, DTItemTypeChance, DTItemGradeChance, DTItemTypeData, CTPortal);
}
//-----------------------------------------------------------------------------------------------------------
void AFPSGameMode::TriggerOnPortalSpawn(const FVector& location)
{
	if (WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	WorldRuler->TriggerOnPortalSpawn(location);
}