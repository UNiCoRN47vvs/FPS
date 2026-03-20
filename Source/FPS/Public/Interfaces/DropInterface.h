#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DropInterface.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UNiagaraSystem;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UDropInterface : public UInterface
{
	GENERATED_BODY()
};
//-----------------------------------------------------------------------------------------------------------
class FPS_API IDropInterface
{
	GENERATED_BODY()

public:
	virtual void ApplyDrop(FItemInvStruct& Item, UNiagaraSystem* Niagara, FLinearColor Color = {}) = 0;
	virtual void DeleteEnemyComponents() = 0;
};
//-----------------------------------------------------------------------------------------------------------