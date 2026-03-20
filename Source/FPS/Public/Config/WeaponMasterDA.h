#pragma once

#include "CoreMinimal.h"
#include "Config/PartMasterDA.h"
#include "Struct/StatStruct.h"
#include "WeaponMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UMetaSoundSource;
class UItemGradeColorDA;
class UNiagaraSystem;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UWeaponMasterDA : public UPartMasterDA
{
	GENERATED_BODY()
public:
	virtual TMap<FString, FText> GetItemInfo() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") TSoftObjectPtr<UAnimMontage> AnimationShoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") TSoftObjectPtr<UAnimMontage> AnimationEquipWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") UAnimMontage* AnimationReloadWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") UAnimMontage* AnimationWeaponEquip;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") UAnimMontage* AnimationWeaponReload;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") UMetaSoundSource* ShootSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") UNiagaraSystem* WeaponEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") UNiagaraSystem* BulletEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") TSoftObjectPtr<UNiagaraSystem> BulletHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") EItemType MagazineTypeForWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "W_M") FName SocketName;
};
//-----------------------------------------------------------------------------------------------------------