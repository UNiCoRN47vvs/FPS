#pragma once

#include "FPS/FPS.h"
#include "Components/ActorComponent.h"
#include "Enums/ItemGrade.h"
#include "DropComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
struct FStuffing
{
	int32 ItemCount = 0;
	TSoftObjectPtr<UPrimaryDataAsset> SoftItemPtr = {};
};
//-----------------------------------------------------------------------------------------------------------
class UNiagaraSystem;
class UItemGradeColorDA;
class UWorldRuler;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDropComponent();

	void SearchDrop(UDataTable* dataTable);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_C") UItemGradeColorDA* ItemGradeColorData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_C") UNiagaraSystem* LootEffect;
protected:
	virtual void BeginPlay() override;
	void StaffingAndSend(TArray<FStuffing> dropItems);

	UPROPERTY() UWorldRuler* WorldRuler;
};
//-----------------------------------------------------------------------------------------------------------