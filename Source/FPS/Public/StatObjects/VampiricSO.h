#pragma once

#include "StatObjects/StatObjectMaster.h"
#include "VampiricSO.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UVampiricSO : public UStatObjectMaster
{
	GENERATED_BODY()
	
public:
	virtual void ApplyStatEffect(FDamageStruct& damageStruct) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "V_SO") float VampiricDamagePercent;


};
//-----------------------------------------------------------------------------------------------------------