#pragma once

#include "Interact/Quest/QuestInteractMaster.h"
#include "UseQuestInteract.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UBoxComponent;
class UWorldRuler;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AUseQuestInteract : public AQuestInteractMaster
{
	GENERATED_BODY()
public:
	AUseQuestInteract();
	virtual void InitInteractQuest() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "U_Q_I") UBoxComponent* CollisionBox;
protected:
	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY() UWorldRuler* WorldRuler;
};
//-----------------------------------------------------------------------------------------------------------