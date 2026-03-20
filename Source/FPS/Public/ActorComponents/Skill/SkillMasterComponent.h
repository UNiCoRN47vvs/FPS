#pragma once

#include "FPS/FPS.h"
#include "Components/ActorComponent.h"
#include "Struct/EnemySkillsData.h"
#include "Struct/StatRange.h"
#include "Struct/DamageStruct.h"
#include "SkillMasterComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API USkillMasterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillMasterComponent();

protected:
	virtual void BeginPlay() override;
};
//-----------------------------------------------------------------------------------------------------------