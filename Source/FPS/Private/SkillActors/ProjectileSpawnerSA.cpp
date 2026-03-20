#include "SkillActors/ProjectileSpawnerSA.h"
#include "Character/CharacterMaster.h"
#include "SkillActors/ProjectileSA.h"
#include "Config/SkillAttackDA.h"
#include "Config/SkillProjectileSpawnerDA.h"
#include "Struct/DamageStruct.h"
//-----------------------------------------------------------------------------------------------------------
void AProjectileSpawnerSA::InitParam(const FDamageStruct& damageStruct, USkillAttackDA* skillAttackDA)
{
	Super::InitParam(damageStruct, skillAttackDA);

	USkillProjectileSpawnerDA* skillProjectileSpawnerDA = Cast<USkillProjectileSpawnerDA>(SkillAttackDA);
	FTimerHandle timerHandle = {};

	CHECK_PTR(skillProjectileSpawnerDA)
	CHECK_PTR(skillProjectileSpawnerDA->SpawnProjectileDA)

	SkillProjectileDA = skillProjectileSpawnerDA->SpawnProjectileDA;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AProjectileSpawnerSA::SpawnProjectile, skillProjectileSpawnerDA->SpawnRateProjectile, true);
}
//-----------------------------------------------------------------------------------------------------------
void AProjectileSpawnerSA::SpawnProjectile()
{
	if (!SkillProjectileDA)
	{
		USkillProjectileSpawnerDA* skillProjectileSpawnerDA = Cast<USkillProjectileSpawnerDA>(SkillAttackDA);
		CHECK_PTR(skillProjectileSpawnerDA)
		CHECK_PTR(skillProjectileSpawnerDA->SpawnProjectileDA)

		SkillProjectileDA = skillProjectileSpawnerDA->SpawnProjectileDA;
	}

	AProjectileSA* projectile = {};
	FActorSpawnParameters spawnParams = {};
	FRotator rotation = GetActorRotation();
	
	CHECK_PTR(SkillProjectileDA->AttackProjectyle)

	DamageStruct.Element1 = SkillProjectileDA->SkillElement1;
	DamageStruct.ElementChanse = DamageStruct.ElementChanse;
	DamageStruct.ImpulseDirection = {};

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < 3; ++i)
	{
		DamageStruct.Damage = SkillProjectileDA->SkillAttackDamage.GetValueFromRange();
		rotation.Yaw = FMath::RandRange(0.0f, 360.0f);
		projectile = GetWorld()->SpawnActor<AProjectileSA>(SkillProjectileDA->AttackProjectyle, GetActorLocation(), rotation, spawnParams);
		if (!projectile)
			continue;

		projectile->InitParam(DamageStruct, SkillProjectileDA);
	}
}
//-----------------------------------------------------------------------------------------------------------