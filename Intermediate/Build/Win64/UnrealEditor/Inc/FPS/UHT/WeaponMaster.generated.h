// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/Weapons/WeaponMaster.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_WeaponMaster_generated_h
#error "WeaponMaster.generated.h already included, missing '#pragma once' in WeaponMaster.h"
#endif
#define FPS_WeaponMaster_generated_h

#define FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_10_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemWeaponMaster_Statics; \
	FPS_API static class UScriptStruct* StaticStruct();


template<> FPS_API UScriptStruct* StaticStruct<struct FItemWeaponMaster>();

#define FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWeaponMaster(); \
	friend struct Z_Construct_UClass_AWeaponMaster_Statics; \
public: \
	DECLARE_CLASS(AWeaponMaster, AItemMaster, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(AWeaponMaster)


#define FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AWeaponMaster(AWeaponMaster&&); \
	AWeaponMaster(const AWeaponMaster&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeaponMaster); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeaponMaster); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWeaponMaster) \
	NO_API virtual ~AWeaponMaster();


#define FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_17_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_20_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class AWeaponMaster>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Items_Weapons_WeaponMaster_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
