// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ActorComponents/Inventory/InventoryComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_InventoryComponent_generated_h
#error "InventoryComponent.generated.h already included, missing '#pragma once' in InventoryComponent.h"
#endif
#define FPS_InventoryComponent_generated_h

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_9_DELEGATE \
FPS_API void FInitInvWidget_DelegateWrapper(const FMulticastScriptDelegate& InitInvWidget);


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemInvStruct_Statics; \
	FPS_API static class UScriptStruct* StaticStruct();


template<> FPS_API UScriptStruct* StaticStruct<struct FItemInvStruct>();

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryComponent(); \
	friend struct Z_Construct_UClass_UInventoryComponent_Statics; \
public: \
	DECLARE_CLASS(UInventoryComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UInventoryComponent)


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_29_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UInventoryComponent(UInventoryComponent&&); \
	UInventoryComponent(const UInventoryComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInventoryComponent) \
	NO_API virtual ~UInventoryComponent();


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_26_PROLOG
#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_29_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UInventoryComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_ActorComponents_Inventory_InventoryComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
