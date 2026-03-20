#pragma once

#include "CoreMinimal.h"
#include "Config/SuppliesMasterDA.h"
#include "Struct/StatRange.h"
#include "MagazineMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class ABulletMaster;
class UNiagaraSystem;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMagazineMasterDA : public USuppliesMasterDA
{
	GENERATED_BODY()
public:
	virtual TMap<FString, FText> GetItemInfo() override;
	UPROPERTY(EditAnywhere, Category = "Magazine Master") FStatRange Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Magazine Master") TSubclassOf<ABulletMaster> BulletClass;


};
//-----------------------------------------------------------------------------------------------------------