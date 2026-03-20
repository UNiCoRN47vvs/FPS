#pragma once

#include "FPS/FPS.h"
#include "GameFramework/Actor.h"
#include "Struct/DamageStruct.h"
#include "BulletMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UNiagaraSystem;
class UNiagaraComponent;
class UBoxComponent;
class UProjectileMovementComponent;
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ABulletMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletMaster();	
	void InitBullet(const FVector& location, const FRotator& rotation, UNiagaraSystem* niagara, TSoftObjectPtr<UNiagaraSystem> BulletHitEffect, const FDamageStruct& damage, AFPSCharacter* playerCharacter);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Master") UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Master") UNiagaraComponent* NiagaraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Master") UProjectileMovementComponent* ProjectileComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void DestroyBullet(UNiagaraComponent* PSystem);
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() UNiagaraSystem* BulletHitEffect;
	FDamageStruct WeaponDamage;
};
//-----------------------------------------------------------------------------------------------------------