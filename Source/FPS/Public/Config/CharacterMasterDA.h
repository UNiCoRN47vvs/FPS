#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MetasoundSource.h"
#include "CharacterMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UCharacterMasterDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Master") UMetaSoundSource* SoundHit;
};
//-----------------------------------------------------------------------------------------------------------