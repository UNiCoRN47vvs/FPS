// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ActorComponents/State/StateMasterComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_StateMasterComponent_generated_h
#error "StateMasterComponent.generated.h already included, missing '#pragma once' in StateMasterComponent.h"
#endif
#define FPS_StateMasterComponent_generated_h

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStateMasterComponent(); \
	friend struct Z_Construct_UClass_UStateMasterComponent_Statics; \
public: \
	DECLARE_CLASS(UStateMasterComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UStateMasterComponent)


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStateMasterComponent(UStateMasterComponent&&); \
	UStateMasterComponent(const UStateMasterComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStateMasterComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStateMasterComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UStateMasterComponent) \
	NO_API virtual ~UStateMasterComponent();


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_18_PROLOG
#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_21_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UStateMasterComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h


#define FOREACH_ENUM_ESTATENAME(op) \
	op(EStateName::Health) \
	op(EStateName::HealthMax) \
	op(EStateName::HealthRegen) \
	op(EStateName::Stamina) \
	op(EStateName::StaminaMax) \
	op(EStateName::StaminaRegen) 

enum class EStateName : uint8;
template<> struct TIsUEnumClass<EStateName> { enum { Value = true }; };
template<> FPS_API UEnum* StaticEnum<EStateName>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
