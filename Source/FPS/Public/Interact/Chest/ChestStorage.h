#pragma once

#include "Interact/InteractMaster.h"
#include "ChestStorage.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class AChestStorage : public AInteractMaster
{
	GENERATED_BODY()
public:
	AChestStorage();
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chest Storage") UStaticMeshComponent* StaticMeshComponent;
};
//-----------------------------------------------------------------------------------------------------------