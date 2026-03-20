#pragma once

#include "Interact/InteractMaster.h"
#include "UpgradeMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UUpgradeComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AUpgradeMaster : public AInteractMaster
{
	GENERATED_BODY()
	
public:	
	AUpgradeMaster();
	UUpgradeComponent* GetUpgradeComponent();
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master") UStaticMeshComponent* StaticMeshComponent;
private:
	UPROPERTY() UUpgradeComponent* UpgradeComponent;
};
