#pragma once

#include "CoreMinimal.h"
#include "Items/ItemMaster.h"
#include "WeaponMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemWeaponMaster
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AWeaponMaster : public AItemMaster
{
	GENERATED_BODY()
public:

	AWeaponMaster();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Master")
	FItemWeaponMaster ItemWeaponInfo;
};
//-----------------------------------------------------------------------------------------------------------