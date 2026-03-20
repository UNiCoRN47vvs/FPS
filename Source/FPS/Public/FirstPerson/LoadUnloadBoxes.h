#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Actor.h"
#include "LoadUnloadBoxes.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UBoxComponent;
class UArrowComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ALoadUnloadBoxes : public AActor
{
	GENERATED_BODY()
	
public:	
	ALoadUnloadBoxes();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "L_U_B") USceneComponent* SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "L_U_B") UBoxComponent* LoadBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "L_U_B") UArrowComponent* ArrowLoad;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "L_U_B") UArrowComponent* ArrowUnload;

protected:
	virtual void BeginPlay() override;
	UFUNCTION() void EndOverlapLoadBox(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);
	UFUNCTION() void LoadLevels();
	UFUNCTION() void UnloadLevels();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "L_U_B") TArray<TSoftObjectPtr<UWorld>> Levels;
	int32 LevelIndexLoad;
	int32 LevelIndexUnload;
};
//-----------------------------------------------------------------------------------------------------------