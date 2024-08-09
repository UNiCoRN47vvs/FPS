// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Widgets/Inventory/InventoryWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInventoryWidget() {}

// Begin Cross Module References
FPS_API UClass* Z_Construct_UClass_UInventoryWidget();
FPS_API UClass* Z_Construct_UClass_UInventoryWidget_NoRegister();
FPS_API UClass* Z_Construct_UClass_UStorageWidget();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UInventoryWidget Function HideInventory
struct Z_Construct_UFunction_UInventoryWidget_HideInventory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Widgets/Inventory/InventoryWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryWidget_HideInventory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UInventoryWidget, nullptr, "HideInventory", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventoryWidget_HideInventory_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventoryWidget_HideInventory_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UInventoryWidget_HideInventory()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventoryWidget_HideInventory_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventoryWidget::execHideInventory)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HideInventory();
	P_NATIVE_END;
}
// End Class UInventoryWidget Function HideInventory

// Begin Class UInventoryWidget
void UInventoryWidget::StaticRegisterNativesUInventoryWidget()
{
	UClass* Class = UInventoryWidget::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "HideInventory", &UInventoryWidget::execHideInventory },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UInventoryWidget);
UClass* Z_Construct_UClass_UInventoryWidget_NoRegister()
{
	return UInventoryWidget::StaticClass();
}
struct Z_Construct_UClass_UInventoryWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Widgets/Inventory/InventoryWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/Inventory/InventoryWidget.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInventoryWidget_HideInventory, "HideInventory" }, // 1254524617
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UInventoryWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UStorageWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventoryWidget_Statics::ClassParams = {
	&UInventoryWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventoryWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventoryWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInventoryWidget()
{
	if (!Z_Registration_Info_UClass_UInventoryWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventoryWidget.OuterSingleton, Z_Construct_UClass_UInventoryWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventoryWidget.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UInventoryWidget>()
{
	return UInventoryWidget::StaticClass();
}
UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInventoryWidget);
UInventoryWidget::~UInventoryWidget() {}
// End Class UInventoryWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventoryWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventoryWidget, UInventoryWidget::StaticClass, TEXT("UInventoryWidget"), &Z_Registration_Info_UClass_UInventoryWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventoryWidget), 4134015018U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventoryWidget_h_1753211435(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventoryWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_InventoryWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
