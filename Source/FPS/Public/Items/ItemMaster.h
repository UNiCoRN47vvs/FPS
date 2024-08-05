#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interfaces/ItemInteract.h"
#include "Structures/ItemStructMaster.h"
#include "ItemMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AItemMaster : public AActor , public IItemInteract
{
	GENERATED_BODY()
	
public:	
	AItemMaster();
	virtual FString GetItemInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Master")
	FString TestString;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Master")
	USphereComponent* ItemSphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Master")
	USceneComponent* ItemScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Master")
	FItemStructMaster ItemInfo;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
//-----------------------------------------------------------------------------------------------------------