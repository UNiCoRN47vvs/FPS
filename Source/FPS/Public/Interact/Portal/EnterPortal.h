#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnterPortal.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UNiagaraComponent;
class UBoxComponent;
class UWorldRuler;
//-----------------------------------------------------------------------------------------------------------
enum EPortalDestination
{
	Home,
	Dungeon
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AEnterPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnterPortal();
	void InitEnterPortal(EPortalDestination destinationPortal);
	UFUNCTION() void UnloadTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enter Portal") USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enter Portal") UNiagaraComponent* NiagaraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enter Portal") UBoxComponent* BoxComponent;
protected:
	virtual void BeginPlay() override;
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	EPortalDestination PortalDestination;
private:
	UPROPERTY() UWorldRuler* WorldRuler;
};
//-----------------------------------------------------------------------------------------------------------