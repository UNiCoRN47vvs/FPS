// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ActorComponents/StorageComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UStorageComponent;
#ifdef FPS_StorageComponent_generated_h
#error "StorageComponent.generated.h already included, missing '#pragma once' in StorageComponent.h"
#endif
#define FPS_StorageComponent_generated_h

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_9_DELEGATE \
FPS_API void FInitInvWidget_DelegateWrapper(const FMulticastScriptDelegate& InitInvWidget, UStorageComponent* StorageComponent);


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FItemInvStruct_Statics; \
	FPS_API static class UScriptStruct* StaticStruct();


template<> FPS_API UScriptStruct* StaticStruct<struct FItemInvStruct>();

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStorageComponent(); \
	friend struct Z_Construct_UClass_UStorageComponent_Statics; \
public: \
	DECLARE_CLASS(UStorageComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UStorageComponent)


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_29_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStorageComponent(UStorageComponent&&); \
	UStorageComponent(const UStorageComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStorageComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStorageComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UStorageComponent) \
	NO_API virtual ~UStorageComponent();


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_26_PROLOG
#define FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_29_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UStorageComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_ActorComponents_StorageComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
