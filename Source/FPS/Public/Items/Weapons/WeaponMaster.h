#pragma once

#include "Items/ItemMaster.h"
#include "Components/ArrowComponent.h"
#include "Animation/AnimMontage.h"
#include "MetasoundSource.h"
#include "Config/WeaponMasterDA.h"
#include "Enums/ElementsType.h"
#include "Struct/MagazineStruct.h"
#include "Struct/DamageStruct.h"
#include "WeaponMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSCharacter;
class UCameraComponent;
class AMagazineMaster;
class UMetaSoundSource;
class UMagazineMasterDA;
class UEnemyMasterDA;
class UEquipmentComponent;
class UAnimInstance;
class ABulletMaster;
class UNiagaraComponent;
class UAudusMasterDA;
struct FDamageStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API AWeaponMaster : public AItemMaster
{
	GENERATED_BODY()
public:
	AWeaponMaster();
	//**************************
	virtual void InitParams(UItemMasterDA* ItemDA = nullptr) override;
	virtual void InitParamsActiveWeapon(USkeletalMeshComponent* PlayerSkeletalMesh, int32 ItemLevel, UEquipmentComponent* Component);
	//**************************
	//Interfaces
	void Fire(AFPSCharacter* Character);
	//**************************
	void StartReload(bool Reloading);
	void WeaponReload(UEquipmentComponent* Component);
	FDamageStruct& GetWeaponDamage();
	//**************************

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master") USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master") UArrowComponent* ArrowComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master") UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Master") bool bIsReloading;

	UPROPERTY() UAnimMontage* AnimationShoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Master") bool bIsAttack;
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	FDamageStruct DamageStruct;
	UPROPERTY() UEquipmentComponent* EquipmentComponent;

private:
	UFUNCTION() void SetbIsMeleeAttack(UAnimMontage* Montage, bool bInterrupted);

	void FireShotGun(FMagazine& magazine, UAudusMasterDA* audusDA);
	template <float valueScale> void FireAutoOrSnipe(FMagazine& magazine, UAudusMasterDA* audusDA);

	UFUNCTION() void SpawnBullet(UAudusMasterDA* audusDA);
	/*UFUNCTION() void MoveBullets();*/
	uint8 bIsMeleeAttack : 1;
	uint8 bIsFireCoolDown : 1;
	int32 WeaponLevel;
	float BulletMoveInterval;
	FLinearColor BulletColor;
	UPROPERTY() UWorld* World;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() UAnimInstance* AnimInstance;
	/*UPROPERTY() FTimerHandle MoveBulletsTimer;*/
	UPROPERTY() UCameraComponent* CameraComponent;
	UPROPERTY() UWeaponMasterDA* WeaponDA;
	UPROPERTY() UMagazineMasterDA* MagazineDA;
};
//-----------------------------------------------------------------------------------------------------------
