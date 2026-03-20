#pragma once

#include "Interact/InteractMaster.h"
#include "Enums/ItemGrade.h"
#include "Portal.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UWorldRuler;
class UPortalComponent;
class UArrowComponent;
class AFPSPlayerController;
class AEnterPortal;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API APortal : public AInteractMaster
{
	GENERATED_BODY()
	
public:
	APortal();
	void OpenPortal(AFPSPlayerController* playerController, TSoftObjectPtr<UWorld> portalLevel, EItemGrade itemGrade);
	void ActivatePortalSpawnCollision();
	UPortalComponent* GetPortalComponent();
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	virtual FInteractStruct GetInteractInfo() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal") UArrowComponent* ArrowComponent;
protected:
	virtual void BeginPlay() override;
	UFUNCTION() void SpawnEnterPortal();
	UFUNCTION(BlueprintCallable)	void OnChildOverlapEnd();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal") USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal") UStaticMeshComponent* StandStaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal") UStaticMeshComponent* SpotStaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal") USphereComponent* BackPortalSphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal") TSoftClassPtr<AEnterPortal> EnterPortalClass;


private:
	UPROPERTY() UWorldRuler* WorldRuler;
	UPROPERTY() UPortalComponent* PortalComponent;
	UPROPERTY() AEnterPortal* EnterPortal;
};
