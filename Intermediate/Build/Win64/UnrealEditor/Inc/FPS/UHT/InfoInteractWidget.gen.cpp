// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Widgets/Interact/InfoInteractWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInfoInteractWidget() {}

// Begin Cross Module References
FPS_API UClass* Z_Construct_UClass_UInfoInteractWidget();
FPS_API UClass* Z_Construct_UClass_UInfoInteractWidget_NoRegister();
FPS_API UFunction* Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Delegate FCantPickUpItem
struct Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/Widgets/Interact/InfoInteractWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FPS, nullptr, "CantPickUpItem__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FCantPickUpItem_DelegateWrapper(const FMulticastScriptDelegate& CantPickUpItem)
{
	CantPickUpItem.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FCantPickUpItem

// Begin Class UInfoInteractWidget
void UInfoInteractWidget::StaticRegisterNativesUInfoInteractWidget()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UInfoInteractWidget);
UClass* Z_Construct_UClass_UInfoInteractWidget_NoRegister()
{
	return UInfoInteractWidget::StaticClass();
}
struct Z_Construct_UClass_UInfoInteractWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Widgets/Interact/InfoInteractWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/Interact/InfoInteractWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextBlock_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Info Interact Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/Interact/InfoInteractWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CantPickUpItem_MetaData[] = {
		{ "Category", "Info Interact Widget" },
		{ "ModuleRelativePath", "Public/Widgets/Interact/InfoInteractWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TextBlock;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_CantPickUpItem;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInfoInteractWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInfoInteractWidget_Statics::NewProp_TextBlock = { "TextBlock", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInfoInteractWidget, TextBlock), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextBlock_MetaData), NewProp_TextBlock_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UInfoInteractWidget_Statics::NewProp_CantPickUpItem = { "CantPickUpItem", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInfoInteractWidget, CantPickUpItem), Z_Construct_UDelegateFunction_FPS_CantPickUpItem__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CantPickUpItem_MetaData), NewProp_CantPickUpItem_MetaData) }; // 4250893044
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInfoInteractWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInfoInteractWidget_Statics::NewProp_TextBlock,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInfoInteractWidget_Statics::NewProp_CantPickUpItem,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInfoInteractWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInfoInteractWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInfoInteractWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInfoInteractWidget_Statics::ClassParams = {
	&UInfoInteractWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UInfoInteractWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UInfoInteractWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInfoInteractWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UInfoInteractWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInfoInteractWidget()
{
	if (!Z_Registration_Info_UClass_UInfoInteractWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInfoInteractWidget.OuterSingleton, Z_Construct_UClass_UInfoInteractWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInfoInteractWidget.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UInfoInteractWidget>()
{
	return UInfoInteractWidget::StaticClass();
}
UInfoInteractWidget::UInfoInteractWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInfoInteractWidget);
UInfoInteractWidget::~UInfoInteractWidget() {}
// End Class UInfoInteractWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInfoInteractWidget, UInfoInteractWidget::StaticClass, TEXT("UInfoInteractWidget"), &Z_Registration_Info_UClass_UInfoInteractWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInfoInteractWidget), 3255780599U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_512614410(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_Interact_InfoInteractWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
