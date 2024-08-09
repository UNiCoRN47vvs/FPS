// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/MainHUD/MainHUDWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EStateName : uint8;
#ifdef FPS_MainHUDWidget_generated_h
#error "MainHUDWidget.generated.h already included, missing '#pragma once' in MainHUDWidget.h"
#endif
#define FPS_MainHUDWidget_generated_h

#define FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execUpdateProgressBar);


#define FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMainHUDWidget(); \
	friend struct Z_Construct_UClass_UMainHUDWidget_Statics; \
public: \
	DECLARE_CLASS(UMainHUDWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UMainHUDWidget)


#define FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMainHUDWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMainHUDWidget(UMainHUDWidget&&); \
	UMainHUDWidget(const UMainHUDWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMainHUDWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMainHUDWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMainHUDWidget) \
	NO_API virtual ~UMainHUDWidget();


#define FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_12_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UMainHUDWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
