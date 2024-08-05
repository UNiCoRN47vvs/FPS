// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/ItemMaster.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef FPS_ItemMaster_generated_h
#error "ItemMaster.generated.h already included, missing '#pragma once' in ItemMaster.h"
#endif
#define FPS_ItemMaster_generated_h

#define FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_12_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemStructMaster_Statics; \
	FPS_API static class UScriptStruct* StaticStruct();


template<> FPS_API UScriptStruct* StaticStruct<struct FItemStructMaster>();

#define FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnOverlapEnd); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAItemMaster(); \
	friend struct Z_Construct_UClass_AItemMaster_Statics; \
public: \
	DECLARE_CLASS(AItemMaster, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(AItemMaster) \
	virtual UObject* _getUObject() const override { return const_cast<AItemMaster*>(this); }


#define FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AItemMaster(AItemMaster&&); \
	AItemMaster(const AItemMaster&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItemMaster); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItemMaster); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AItemMaster) \
	NO_API virtual ~AItemMaster();


#define FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_22_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class AItemMaster>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Items_ItemMaster_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
