#pragma once

#include "FPS/FPS.h"
#include "Items/ItemMaster.h"
#include "Config/SuppliesMasterDA.h"
#include "Config/PortalStoneMasterDA.h"
#include "Config/ConsumableSuppliesMasterDA.h"
#include "SuppliesMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UEventBus;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemSuppliesMaster
{
	GENERATED_BODY()

	double UseValue;
	TSoftObjectPtr<UStaticMesh> StaticMesh;

};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ASuppliesMaster : public AItemMaster
{
	GENERATED_BODY()
public:
	ASuppliesMaster();
	virtual void InitParams(UItemMasterDA* ItemDA = nullptr) override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Master") UStaticMeshComponent* StaticMeshComponent;
};
//-----------------------------------------------------------------------------------------------------------