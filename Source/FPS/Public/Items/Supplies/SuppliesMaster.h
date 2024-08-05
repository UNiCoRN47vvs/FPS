#pragma once

#include "CoreMinimal.h"
#include "Items/ItemMaster.h"
#include "SuppliesMaster.generated.h"
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
};
//-----------------------------------------------------------------------------------------------------------