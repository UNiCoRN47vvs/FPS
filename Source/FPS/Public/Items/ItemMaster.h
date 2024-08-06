#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interfaces/ItemInteract.h"
#include "ItemMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemStructMaster
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")
	FText ItemDesc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")
	TSoftObjectPtr<UTexture2D> ItemIcon;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AItemMaster : public AActor , public IItemInteract
{
	GENERATED_BODY()
	
public:	
	AItemMaster();
	virtual FItemStructMaster GetItemInfo() override;
	virtual void InteractWithActor(AFPSCharacter* PlayerCharacter) override;

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