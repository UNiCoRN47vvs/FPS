// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/Inventory/ChestWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_ChestWidget_generated_h
#error "ChestWidget.generated.h already included, missing '#pragma once' in ChestWidget.h"
#endif
#define FPS_ChestWidget_generated_h

#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h_9_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUChestWidget(); \
	friend struct Z_Construct_UClass_UChestWidget_Statics; \
public: \
	DECLARE_CLASS(UChestWidget, UStorageWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UChestWidget)


#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h_9_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UChestWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UChestWidget(UChestWidget&&); \
	UChestWidget(const UChestWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UChestWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UChestWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UChestWidget) \
	NO_API virtual ~UChestWidget();


#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h_6_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h_9_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UChestWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_ChestWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
