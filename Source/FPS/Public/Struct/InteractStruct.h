#pragma once

#include "CoreMinimal.h"
#include "InteractStruct.generated.h"

USTRUCT(BlueprintType)
struct FInteractStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")	FString InteractButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")	FString IteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")	FString ItemName;
};
