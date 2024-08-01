// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ActorComponents/State/HealthStaminaComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EStateName : uint8;
#ifdef FPS_HealthStaminaComponent_generated_h
#error "HealthStaminaComponent.generated.h already included, missing '#pragma once' in HealthStaminaComponent.h"
#endif
#define FPS_HealthStaminaComponent_generated_h

#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_10_DELEGATE \
FPS_API void FChangeState_DelegateWrapper(const FMulticastScriptDelegate& ChangeState, EStateName StateName, double CurrentValue, double MaxValue);


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execWasteStaminaTimerManager); \
	DECLARE_FUNCTION(execRegenTimerManager); \
	DECLARE_FUNCTION(execChangeStateValue);


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHealthStaminaComponent(); \
	friend struct Z_Construct_UClass_UHealthStaminaComponent_Statics; \
public: \
	DECLARE_CLASS(UHealthStaminaComponent, UStateMasterComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UHealthStaminaComponent)


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UHealthStaminaComponent(UHealthStaminaComponent&&); \
	UHealthStaminaComponent(const UHealthStaminaComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHealthStaminaComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHealthStaminaComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHealthStaminaComponent) \
	NO_API virtual ~UHealthStaminaComponent();


#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_12_PROLOG
#define FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UHealthStaminaComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_ActorComponents_State_HealthStaminaComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
