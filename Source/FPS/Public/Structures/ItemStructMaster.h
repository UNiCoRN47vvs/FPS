#pragma once

#include "CoreMinimal.h"
#include "ItemStructMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FPS_API FItemStructMaster
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct Master")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct Master")
	FText ItemDesc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct Master")
	TSoftObjectPtr<UTexture2D> ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct Master")
	TSoftObjectPtr<USkeletalMesh> ItemSkeletalMesh;

};
//-----------------------------------------------------------------------------------------------------------