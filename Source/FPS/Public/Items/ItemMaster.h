#pragma once
#include "Interact/InteractMaster.h"
#include "Interfaces/ItemInfo.h"
#include "Config/ItemMasterDA.h"
#include "ItemMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemStructMaster
{
	GENERATED_BODY()

	int32 ItemCount;
	int32 ItemCountMax;
	double ItemWeight;
	EItemType ItemType;
	FName ItemName;
	FText ItemDesc;
	TSoftObjectPtr<UTexture2D> ItemIcon;
	TSoftClassPtr<AItemMaster> ItemClass;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AItemMaster : public AInteractMaster, public IItemInfo
{
	GENERATED_BODY()
	
public:	
	AItemMaster();
	//**************************
	virtual void InitParams(UItemMasterDA* ItemDA = nullptr);
	//**************************
	//Getters
	virtual FItemStructMaster GetItemInfo() override;
	virtual FInteractStruct GetInteractInfo() override;
	template <typename DataAssetClass>	DataAssetClass* GetConfigDA()
	{
		return Cast<DataAssetClass>(DataAssetConfig);
	};
	//**************************
	//Interfaces
	virtual void InteractWithActor(ACharacterMaster* PlayerCharacter) override;
	//**************************
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Master")	int32 ItemCount;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset Config")	UPrimaryDataAsset* DataAssetConfig;
};
//-----------------------------------------------------------------------------------------------------------