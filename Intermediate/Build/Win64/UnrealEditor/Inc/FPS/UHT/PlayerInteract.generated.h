// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interfaces/PlayerInteract.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_PlayerInteract_generated_h
#error "PlayerInteract.generated.h already included, missing '#pragma once' in PlayerInteract.h"
#endif
#define FPS_PlayerInteract_generated_h

#define FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FPS_API UPlayerInteract(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPlayerInteract(UPlayerInteract&&); \
	UPlayerInteract(const UPlayerInteract&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FPS_API, UPlayerInteract); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPlayerInteract); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPlayerInteract) \
	FPS_API virtual ~UPlayerInteract();


#define FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUPlayerInteract(); \
	friend struct Z_Construct_UClass_UPlayerInteract_Statics; \
public: \
	DECLARE_CLASS(UPlayerInteract, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/FPS"), FPS_API) \
	DECLARE_SERIALIZER(UPlayerInteract)


#define FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_GENERATED_UINTERFACE_BODY() \
	FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IPlayerInteract() {} \
public: \
	typedef UPlayerInteract UClassType; \
	typedef IPlayerInteract ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_7_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h_10_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UPlayerInteract>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Interfaces_PlayerInteract_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
