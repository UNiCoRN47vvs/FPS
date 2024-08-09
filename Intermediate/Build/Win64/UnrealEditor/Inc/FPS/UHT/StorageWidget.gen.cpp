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
FPS_API UClass* Z_Construct_UClass_UStorageWidget();
FPS_API UClass* Z_Construct_UClass_UStorageWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UStorageWidget
void UStorageWidget::StaticRegisterNativesUStorageWidget()
{
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
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Widgets/Inventory/StorageWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/Inventory/StorageWidget.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStorageWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UStorageWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStorageWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStorageWidget_Statics::ClassParams = {
	&UStorageWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
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
		{ Z_Construct_UClass_UStorageWidget, UStorageWidget::StaticClass, TEXT("UStorageWidget"), &Z_Registration_Info_UClass_UStorageWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStorageWidget), 1530148346U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_3107066908(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Inventory_StorageWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
