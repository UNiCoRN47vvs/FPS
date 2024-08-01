// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_ProgressBarWidget_generated_h
#error "ProgressBarWidget.generated.h already included, missing '#pragma once' in ProgressBarWidget.h"
#endif
#define FPS_ProgressBarWidget_generated_h

#define FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUProgressBarWidget(); \
	friend struct Z_Construct_UClass_UProgressBarWidget_Statics; \
public: \
	DECLARE_CLASS(UProgressBarWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UProgressBarWidget)


#define FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UProgressBarWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UProgressBarWidget(UProgressBarWidget&&); \
	UProgressBarWidget(const UProgressBarWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UProgressBarWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UProgressBarWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UProgressBarWidget) \
	NO_API virtual ~UProgressBarWidget();


#define FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_9_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_12_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UProgressBarWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
