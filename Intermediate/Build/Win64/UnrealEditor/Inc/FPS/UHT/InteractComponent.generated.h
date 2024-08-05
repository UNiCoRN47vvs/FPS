// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ActorComponents/Interact/InteractComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_InteractComponent_generated_h
#error "InteractComponent.generated.h already included, missing '#pragma once' in InteractComponent.h"
#endif
#define FPS_InteractComponent_generated_h

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInteractComponent(); \
	friend struct Z_Construct_UClass_UInteractComponent_Statics; \
public: \
	DECLARE_CLASS(UInteractComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UInteractComponent)


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UInteractComponent(UInteractComponent&&); \
	UInteractComponent(const UInteractComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInteractComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInteractComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInteractComponent) \
	NO_API virtual ~UInteractComponent();


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_12_PROLOG
#define FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_15_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UInteractComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
