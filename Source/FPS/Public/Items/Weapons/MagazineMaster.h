#pragma once

#include "CoreMinimal.h"
#include "Items/Supplies/SuppliesMaster.h"
#include "Config/MagazineMasterDA.h"
#include "MagazineMaster.generated.h"

//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AMagazineMaster : public ASuppliesMaster
{
	GENERATED_BODY()
public:
	AMagazineMaster();
	virtual void InitParams(UItemMasterDA* ItemDA = nullptr) override;
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
};
//-----------------------------------------------------------------------------------------------------------