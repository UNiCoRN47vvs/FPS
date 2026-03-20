#pragma once

#include "FPS/FPS.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UMetaSoundSource;
class UWorldRuler;
//-----------------------------------------------------------------------------------------------------------
UCLASS(minimalapi)
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSGameMode();
	UFUNCTION(BlueprintCallable) void TriggerOnPortalSpawn(const FVector& location);

protected:
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UDataTable* DTEnemiesData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UDataTable* DTBossesData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UDataTable* DTItemTypeChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UDataTable* DTItemGradeChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UDataTable* DTItemTypeData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UCurveTable* CTPortal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") UMetaSoundSource* BattleSong;																 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") int32 TimeCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") double TimeBetweenSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS_G_M") TSoftObjectPtr<UWorld> MainHUB;
	UPROPERTY() UWorldRuler* WorldRuler;

};
//-----------------------------------------------------------------------------------------------------------

