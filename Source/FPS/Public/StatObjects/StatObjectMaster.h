#pragma once

#include "FPS/FPS.h"
#include "UObject/NoExportTypes.h"
#include "Struct/DamageStruct.h"
#include "StatObjectMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UStateMasterComponent;
class UNiagaraSystem;
class UNiagaraComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class FPS_API UStatObjectMaster : public UObject
{
	GENERATED_BODY()
public:
	virtual void InitParams(UStateMasterComponent* stateComponent, float effectChanse);
	virtual void DestroyStatObject();
	virtual void ApplyStatEffect(FDamageStruct& damageStruct);
	
protected:
	virtual void PostInitProperties() override;
	float EffectChanse;
	FDamageStruct DamageStruct;
	UPROPERTY() UStateMasterComponent* StateComponent;
};
//-----------------------------------------------------------------------------------------------------------