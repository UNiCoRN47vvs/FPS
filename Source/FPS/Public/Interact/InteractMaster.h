#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interfaces/ItemInteract.h"
#include "Interfaces/InteractInfo.h"
#include "Struct/InteractStruct.h"
#include "InteractMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class IPlayerInteract;
class ACharacterMaster;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AInteractMaster : public AActor, public IItemInteract, public IInteractInfo
{
	GENERATED_BODY()
	
public:	
	AInteractMaster();
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Master")	USceneComponent* ItemScene;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Master")	FInteractStruct InteractInfo;
private:
	IPlayerInteract* PlayerInterface;

};
//-----------------------------------------------------------------------------------------------------------