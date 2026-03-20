#include "AnimNotify/PlayerAttackNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/CharacterMaster.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "Items/Weapons/WeaponMaster.h"
#include "Struct/DamageStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UPlayerAttackNotify::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	bool bIsHit = false;
	UEquipmentComponent* equipmentComponent = nullptr;
	ACharacterMaster* enemyCharacter = nullptr;
	AWeaponMaster* activeWeapon = nullptr;
	float radius = 140.0f;
	FVector location = {};
	FDamageStruct damageStruct = {};
	FHitResult targetHitResult = {};
	TArray<AActor*> ignoreActors = {};
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType = {};
	TArray<FHitResult> outHitResult = {};

	CHECK_PTR(MeshComponent)
	CHECK_PTR(MeshComponent->GetOwner())

	equipmentComponent = MeshComponent->GetOwner()->FindComponentByClass<UEquipmentComponent>();

	CHECK_PTR(equipmentComponent)
	CHECK_PTR(equipmentComponent->ActiveWeapon)
	
	activeWeapon = equipmentComponent->ActiveWeapon;

	location = activeWeapon->ArrowComponent->GetComponentLocation();
	objectType.Add(EObjectTypeQuery::ObjectTypeQuery3);

	ignoreActors.Add(MeshComponent->GetOwner());
	bIsHit = UKismetSystemLibrary::SphereTraceMultiForObjects(equipmentComponent->GetWorld(), location, location, radius,
		objectType, false, ignoreActors, EDrawDebugTrace::None, outHitResult, true, FLinearColor::Red, FLinearColor::Green, 3.0);

	if (!bIsHit)
		return;

	for (const FHitResult& item : outHitResult)
	{
		if (item.GetActor()->ActorHasTag(FName("Enemy")))
		{
			enemyCharacter = Cast<ACharacterMaster>(item.GetActor());
			if (!IsValid(enemyCharacter))
			{
				ALARM_LOG
				return;
			}
			damageStruct = activeWeapon->GetWeaponDamage();
			enemyCharacter->DealDamage(damageStruct, item);
		}	
	}
}
