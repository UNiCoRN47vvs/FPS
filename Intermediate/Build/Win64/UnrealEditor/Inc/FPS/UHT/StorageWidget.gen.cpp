// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Widgets/Inventory/StorageWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStorageWidget() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
FPS_API UClass* Z_Construct_UClass_UStorageComponent_NoRegister();
FPS_API UClass* Z_Construct_UClass_UStorageInterface_NoRegister();
FPS_API UClass* Z_Construct_UClass_UStorageWidget();
FPS_API UClass* Z_Construct_UClass_UStorageWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUniformGridPanel_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UStorageWidget Function InitStorageWidget
struct Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics
{
	struct StorageWidget_eventInitStorageWidget_Parms
	{
		UStorageComponent* StorageComponent;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StorageComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StorageComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::NewProp_StorageComponent = { "StorageComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StorageWidget_eventInitStorageWidget_Parms, StorageComponent), Z_Construct_UClass_UStorageComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StorageComponent_MetaData), NewProp_StorageComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::NewProp_StorageComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStorageWidget, nullptr, "InitStorageWidget", nullptr, nullptr, Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::PropPointers), sizeof(Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::StorageWidget_eventInitStorageWidget_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::StorageWidget_eventInitStorageWidget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UStorageWidget_InitStorageWidget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStorageWidget_InitStorageWidget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UStorageWidget::execInitStorageWidget)
{
	P_GET_OBJECT(UStorageComponent,Z_Param_StorageComponent);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitStorageWidget(Z_Param_StorageComponent);
	P_NATIVE_END;
}
// End Class UStorageWidget Function InitStorageWidget

// Begin Class UStorageWidget Function UpdateInventoryWidget
struct Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UStorageWidget, nullptr, "UpdateInventoryWidget", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UStorageWidget::execUpdateInventoryWidget)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateInventoryWidget();
	P_NATIVE_END;
}
// End Class UStorageWidget Function UpdateInventoryWidget

// Begin Class UStorageWidget
void UStorageWidget::StaticRegisterNativesUStorageWidget()
{
	UClass* Class = UStorageWidget::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitStorageWidget", &UStorageWidget::execInitStorageWidget },
		{ "UpdateInventoryWidget", &UStorageWidget::execUpdateInventoryWidget },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UStorageWidget);
UClass* Z_Construct_UClass_UStorageWidget_NoRegister()
{
	return UStorageWidget::StaticClass();
}
struct Z_Construct_UClass_UStorageWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Widgets/Inventory/StorageWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniformGridPanel_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Inventory Slot Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ButtonClose_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Inventory Slot Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotWidget_MetaData[] = {
		{ "Category", "Inventory Slot Widget" },
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UniformGridPanel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ButtonClose;
	static const UECodeGen_Private::FClassPropertyParams NewProp_SlotWidget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UStorageWidget_InitStorageWidget, "InitStorageWidget" }, // 1283236972
		{ &Z_Construct_UFunction_UStorageWidget_UpdateInventoryWidget, "UpdateInventoryWidget" }, // 120706866
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStorageWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStorageWidget_Statics::NewProp_UniformGridPanel = { "UniformGridPanel", nullptr, (EPropertyFlags)0x001000000008001c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageWidget, UniformGridPanel), Z_Construct_UClass_UUniformGridPanel_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniformGridPanel_MetaData), NewProp_UniformGridPanel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UStorageWidget_Statics::NewProp_ButtonClose = { "ButtonClose", nullptr, (EPropertyFlags)0x001000000008001c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageWidget, ButtonClose), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ButtonClose_MetaData), NewProp_ButtonClose_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UStorageWidget_Statics::NewProp_SlotWidget = { "SlotWidget", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UStorageWidget, SlotWidget), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotWidget_MetaData), NewProp_SlotWidget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UStorageWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageWidget_Statics::NewProp_UniformGridPanel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageWidget_Statics::NewProp_ButtonClose,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UStorageWidget_Statics::NewProp_SlotWidget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UStorageWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UStorageWidget_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UStorageInterface_NoRegister, (int32)VTABLE_OFFSET(UStorageWidget, IStorageInterface), false },  // 1333442267
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStorageWidget_Statics::ClassParams = {
	&UStorageWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UStorageWidget_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UStorageWidget_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UStorageWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UStorageWidget()
{
	if (!Z_Registration_Info_UClass_UStorageWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStorageWidget.OuterSingleton, Z_Construct_UClass_UStorageWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UStorageWidget.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UStorageWidget>()
{
	return UStorageWidget::StaticClass();
}
UStorageWidget::UStorageWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UStorageWidget);
UStorageWidget::~UStorageWidget() {}
// End Class UStorageWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UStorageWidget, UStorageWidget::StaticClass, TEXT("UStorageWidget"), &Z_Registration_Info_UClass_UStorageWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStorageWidget), 441088409U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_4242314330(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
