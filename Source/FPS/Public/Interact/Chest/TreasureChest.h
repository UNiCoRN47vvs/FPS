#pragma once

#include "Interact/InteractMaster.h"
#include "Interfaces/DropInterface.h"
#include "TreasureChest.generated.h"
//-----------------------------------------------------------------------------------------------------------
class ACharacterMaster;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ATreasureChest : public AInteractMaster, public IDropInterface
{
	GENERATED_BODY()
public:
	ATreasureChest();
	virtual FInteractStruct GetInteractInfo() override;
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual void ApplyDrop(FItemInvStruct& Item, UNiagaraSystem* Niagara, FLinearColor Color) override;
	virtual void DeleteEnemyComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Treasure Chest") UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot") UDataTable* DTSpecialDrop;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot") USoundWave* OpenSound;

protected:
	virtual void BeginPlay() override;
};
//-----------------------------------------------------------------------------------------------------------