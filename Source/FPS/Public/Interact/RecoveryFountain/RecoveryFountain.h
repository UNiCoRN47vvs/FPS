#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInfo.h"
#include "Interfaces/ItemInteract.h"
#include "Struct/InteractStruct.h"
#include "RecoveryFountain.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ARecoveryFountain : public AActor, public IInteractInfo, public IItemInteract
{
	GENERATED_BODY()
	
public:	
	ARecoveryFountain();
	virtual FInteractStruct GetInteractInfo() override;
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_F") UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_F") USoundWave* InteractSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_F") float SpawnChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_F") float InteractCost;
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_F") FInteractStruct InteractStruct;
};
//-----------------------------------------------------------------------------------------------------------