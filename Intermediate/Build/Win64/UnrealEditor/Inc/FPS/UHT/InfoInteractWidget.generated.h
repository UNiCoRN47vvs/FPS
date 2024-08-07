// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/Interact/InfoInteractWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_InfoInteractWidget_generated_h
#error "InfoInteractWidget.generated.h already included, missing '#pragma once' in InfoInteractWidget.h"
#endif
#define FPS_InfoInteractWidget_generated_h

#define FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_8_DELEGATE \
FPS_API void FCantPickUpItem_DelegateWrapper(const FMulticastScriptDelegate& CantPickUpItem);


#define FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInfoInteractWidget(); \
	friend struct Z_Construct_UClass_UInfoInteractWidget_Statics; \
public: \
	DECLARE_CLASS(UInfoInteractWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UInfoInteractWidget)


#define FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInfoInteractWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UInfoInteractWidget(UInfoInteractWidget&&); \
	UInfoInteractWidget(const UInfoInteractWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInfoInteractWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInfoInteractWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInfoInteractWidget) \
	NO_API virtual ~UInfoInteractWidget();


#define FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_10_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_13_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UInfoInteractWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
