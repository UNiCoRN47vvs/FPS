#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MetasoundSource.h"
#include "Enums/ItemGrade.h"
#include "Enums/ElementsType.h"
#include "Enums/ItemType.h"
#include "Struct/CurrencyStruct.h"
#include "Struct/StatStruct.h"
#include "ItemMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AItemMaster;
class AFPSPlayerController;
class UEventBus;
struct FStatRange;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UItemMasterDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual bool UseItem(AFPSPlayerController* playerController);
	virtual TMap<FString, FText> GetItemInfo();
	virtual FStatRange GetItemDamage();
	virtual TMap<EStateName, float> GetItemStat();
	virtual void ApplyRuneData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") int32 ItemCountMax;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") float ItemWeight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") float UseValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") EItemGrade ItemGrade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") EElementsType ElementType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") FText ItemDesc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") FString InteractButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") FString IteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") FCurrency ItemCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") TSoftObjectPtr<UTexture2D> ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") TSoftClassPtr<AItemMaster> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") TSoftObjectPtr<UItemMasterDA> NextUpgrade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_M") FStatStruct StatStruct;
};
//-----------------------------------------------------------------------------------------------------------