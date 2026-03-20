#pragma once

#include "Interact/InteractMaster.h"
#include "CraftMachine.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ACraftMachine : public AInteractMaster
{
	GENERATED_BODY()
	
public:	
	ACraftMachine();
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_M") UStaticMeshComponent* StaticMeshComponent;
protected:
	virtual void BeginPlay() override;

};
//-----------------------------------------------------------------------------------------------------------