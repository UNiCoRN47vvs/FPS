// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interfaces/ItemInteract.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_ItemInteract_generated_h
#error "ItemInteract.generated.h already included, missing '#pragma once' in ItemInteract.h"
#endif
#define FPS_ItemInteract_generated_h

#define FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FPS_API UItemInteract(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UItemInteract(UItemInteract&&); \
	UItemInteract(const UItemInteract&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FPS_API, UItemInteract); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UItemInteract); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UItemInteract) \
	FPS_API virtual ~UItemInteract();


#define FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUItemInteract(); \
	friend struct Z_Construct_UClass_UItemInteract_Statics; \
public: \
	DECLARE_CLASS(UItemInteract, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/FPS"), FPS_API) \
	DECLARE_SERIALIZER(UItemInteract)


#define FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_GENERATED_UINTERFACE_BODY() \
	FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IItemInteract() {} \
public: \
	typedef UItemInteract UClassType; \
	typedef IItemInteract ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_9_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UItemInteract>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Interfaces_ItemInteract_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
