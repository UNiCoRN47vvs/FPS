#pragma once

#include "CoreMinimal.h"
#include "Config/ItemMasterDA.h"
#include "Enums/FiringMode.h"
#include "PartMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPartMasterDA : public UItemMasterDA
{
	GENERATED_BODY()
public:
	virtual TMap<FString, FText> GetItemInfo() override;
	virtual FStatRange GetItemDamage() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_M") EFiringMode FiringMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_M") FStatRange Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_M") float AttackSpeed;
};
//-----------------------------------------------------------------------------------------------------------