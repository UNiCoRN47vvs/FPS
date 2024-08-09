#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AItemMaster;
//-----------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitInvWidget);
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemInvStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") bool bOccupied;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") int ItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") int ItemCountMax;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") double ItemValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") FText ItemDesc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") TSoftObjectPtr<UTexture2D> ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") TSoftClassPtr<AItemMaster> ItemClass;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	TArray<FItemInvStruct> GetInventory();
	void SetItemFromIndex(FItemInvStruct Item, int Index);
	bool PickUpItem(FItemInvStruct& ItemStruct);
	UPROPERTY(BlueprintAssignable, Category = "Inventory Component") FInitInvWidget InitInvWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Component") int InvMaxSlots;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Component") int InvSlotsPerRow;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Component") TArray<FItemInvStruct> Inventory;
};
//-----------------------------------------------------------------------------------------------------------
