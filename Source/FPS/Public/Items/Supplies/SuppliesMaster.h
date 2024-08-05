#pragma once

#include "CoreMinimal.h"
#include "Items/ItemMaster.h"
#include "SuppliesMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemSuppliesMaster
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")
	TSoftObjectPtr<UStaticMesh> StaticMesh;

};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ASuppliesMaster : public AItemMaster
{
	GENERATED_BODY()
public:
	ASuppliesMaster();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Master")
	FItemSuppliesMaster ItemWeaponInfo;
};
//-----------------------------------------------------------------------------------------------------------