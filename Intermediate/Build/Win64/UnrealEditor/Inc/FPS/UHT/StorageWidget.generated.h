// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/Inventory/StorageWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_StorageWidget_generated_h
#error "StorageWidget.generated.h already included, missing '#pragma once' in StorageWidget.h"
#endif
#define FPS_StorageWidget_generated_h

#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStorageWidget(); \
	friend struct Z_Construct_UClass_UStorageWidget_Statics; \
public: \
	DECLARE_CLASS(UStorageWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UStorageWidget)


#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UStorageWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStorageWidget(UStorageWidget&&); \
	UStorageWidget(const UStorageWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStorageWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStorageWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UStorageWidget) \
	NO_API virtual ~UStorageWidget();


#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_12_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_15_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UStorageWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
