// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Widgets/ProgressBar/ProgressBarWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProgressBarWidget() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
FPS_API UClass* Z_Construct_UClass_UProgressBarWidget();
FPS_API UClass* Z_Construct_UClass_UProgressBarWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UProgressBar_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UProgressBarWidget
void UProgressBarWidget::StaticRegisterNativesUProgressBarWidget()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UProgressBarWidget);
UClass* Z_Construct_UClass_UProgressBarWidget_NoRegister()
{
	return UProgressBarWidget::StaticClass();
}
struct Z_Construct_UClass_UProgressBarWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Widgets/ProgressBar/ProgressBarWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/ProgressBar/ProgressBarWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProgressBar_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Progress Bar Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/ProgressBar/ProgressBarWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ValueTextBlock_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Progress Bar Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/ProgressBar/ProgressBarWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProgressBarColor_MetaData[] = {
		{ "Category", "Progress Bar Widget" },
		{ "ModuleRelativePath", "Public/Widgets/ProgressBar/ProgressBarWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProgressBar;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ValueTextBlock;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ProgressBarColor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UProgressBarWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UProgressBarWidget_Statics::NewProp_ProgressBar = { "ProgressBar", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProgressBarWidget, ProgressBar), Z_Construct_UClass_UProgressBar_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProgressBar_MetaData), NewProp_ProgressBar_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UProgressBarWidget_Statics::NewProp_ValueTextBlock = { "ValueTextBlock", nullptr, (EPropertyFlags)0x001000000008001c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProgressBarWidget, ValueTextBlock), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ValueTextBlock_MetaData), NewProp_ValueTextBlock_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UProgressBarWidget_Statics::NewProp_ProgressBarColor = { "ProgressBarColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UProgressBarWidget, ProgressBarColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProgressBarColor_MetaData), NewProp_ProgressBarColor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UProgressBarWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProgressBarWidget_Statics::NewProp_ProgressBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProgressBarWidget_Statics::NewProp_ValueTextBlock,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UProgressBarWidget_Statics::NewProp_ProgressBarColor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProgressBarWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UProgressBarWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UProgressBarWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UProgressBarWidget_Statics::ClassParams = {
	&UProgressBarWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UProgressBarWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UProgressBarWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UProgressBarWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UProgressBarWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UProgressBarWidget()
{
	if (!Z_Registration_Info_UClass_UProgressBarWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UProgressBarWidget.OuterSingleton, Z_Construct_UClass_UProgressBarWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UProgressBarWidget.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UProgressBarWidget>()
{
	return UProgressBarWidget::StaticClass();
}
UProgressBarWidget::UProgressBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UProgressBarWidget);
UProgressBarWidget::~UProgressBarWidget() {}
// End Class UProgressBarWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UProgressBarWidget, UProgressBarWidget::StaticClass, TEXT("UProgressBarWidget"), &Z_Registration_Info_UClass_UProgressBarWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UProgressBarWidget), 1721665301U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_2521684960(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_ProgressBar_ProgressBarWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
