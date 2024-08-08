// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Widgets/Inventory/InventorySlotWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FPS_InventorySlotWidget_generated_h
#error "InventorySlotWidget.generated.h already included, missing '#pragma once' in InventorySlotWidget.h"
#endif
#define FPS_InventorySlotWidget_generated_h

#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventorySlotWidget(); \
	friend struct Z_Construct_UClass_UInventorySlotWidget_Statics; \
public: \
	DECLARE_CLASS(UInventorySlotWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FPS"), NO_API) \
	DECLARE_SERIALIZER(UInventorySlotWidget) \
	virtual UObject* _getUObject() const override { return const_cast<UInventorySlotWidget*>(this); }


#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventorySlotWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UInventorySlotWidget(UInventorySlotWidget&&); \
	UInventorySlotWidget(const UInventorySlotWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventorySlotWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventorySlotWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventorySlotWidget) \
	NO_API virtual ~UInventorySlotWidget();


#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h_10_PROLOG
#define FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h_13_INCLASS_NO_PURE_DECLS \
	FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FPS_API UClass* StaticClass<class UInventorySlotWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventorySlotWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
