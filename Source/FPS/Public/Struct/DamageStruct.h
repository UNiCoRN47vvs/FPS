#pragma once

#include "CoreMinimal.h"
#include "Enums/ElementsType.h"
//-----------------------------------------------------------------------------------------------------------
class UStateMasterComponent;
//-----------------------------------------------------------------------------------------------------------
struct FDamageStruct
{
	AActor* DamageOwner = nullptr;
	UStateMasterComponent* DamageOwnerComponent = nullptr;
	float Damage = 0.0f;
	float ElementChanse = 0.0f;
	EElementsType Element1 = EElementsType::None;
	FVector ImpulseDirection = {};
	
};
