// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Widgets/MainHUD/MainHUDWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainHUDWidget() {}

// Begin Cross Module References
FPS_API UClass* Z_Construct_UClass_UMainHUDWidget();
FPS_API UClass* Z_Construct_UClass_UMainHUDWidget_NoRegister();
FPS_API UClass* Z_Construct_UClass_UProgressBarWidget_NoRegister();
FPS_API UEnum* Z_Construct_UEnum_FPS_EStateName();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UMainHUDWidget Function UpdateProgressBar
struct Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics
{
	struct MainHUDWidget_eventUpdateProgressBar_Parms
	{
		EStateName StateName;
		double CurrentValue;
		double MaxValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Widgets/MainHUD/MainHUDWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_StateName_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_StateName;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_CurrentValue;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_StateName_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_StateName = { "StateName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainHUDWidget_eventUpdateProgressBar_Parms, StateName), Z_Construct_UEnum_FPS_EStateName, METADATA_PARAMS(0, nullptr) }; // 2250722387
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_CurrentValue = { "CurrentValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainHUDWidget_eventUpdateProgressBar_Parms, CurrentValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainHUDWidget_eventUpdateProgressBar_Parms, MaxValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_StateName_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_StateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_CurrentValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::NewProp_MaxValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainHUDWidget, nullptr, "UpdateProgressBar", nullptr, nullptr, Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::MainHUDWidget_eventUpdateProgressBar_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::MainHUDWidget_eventUpdateProgressBar_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMainHUDWidget::execUpdateProgressBar)
{
	P_GET_ENUM(EStateName,Z_Param_StateName);
	P_GET_PROPERTY(FDoubleProperty,Z_Param_CurrentValue);
	P_GET_PROPERTY(FDoubleProperty,Z_Param_MaxValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateProgressBar(EStateName(Z_Param_StateName),Z_Param_CurrentValue,Z_Param_MaxValue);
	P_NATIVE_END;
}
// End Class UMainHUDWidget Function UpdateProgressBar

// Begin Class UMainHUDWidget
void UMainHUDWidget::StaticRegisterNativesUMainHUDWidget()
{
	UClass* Class = UMainHUDWidget::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "UpdateProgressBar", &UMainHUDWidget::execUpdateProgressBar },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMainHUDWidget);
UClass* Z_Construct_UClass_UMainHUDWidget_NoRegister()
{
	return UMainHUDWidget::StaticClass();
}
struct Z_Construct_UClass_UMainHUDWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "Widgets/MainHUD/MainHUDWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/MainHUD/MainHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WBPHealth_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Main HUD Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/MainHUD/MainHUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WBPStamina_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "Main HUD Widget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Widgets/MainHUD/MainHUDWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WBPHealth;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WBPStamina;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMainHUDWidget_UpdateProgressBar, "UpdateProgressBar" }, // 3628006356
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMainHUDWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainHUDWidget_Statics::NewProp_WBPHealth = { "WBPHealth", nullptr, (EPropertyFlags)0x001000000008001c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainHUDWidget, WBPHealth), Z_Construct_UClass_UProgressBarWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WBPHealth_MetaData), NewProp_WBPHealth_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainHUDWidget_Statics::NewProp_WBPStamina = { "WBPStamina", nullptr, (EPropertyFlags)0x001000000008001c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainHUDWidget, WBPStamina), Z_Construct_UClass_UProgressBarWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WBPStamina_MetaData), NewProp_WBPStamina_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMainHUDWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainHUDWidget_Statics::NewProp_WBPHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainHUDWidget_Statics::NewProp_WBPStamina,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainHUDWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UMainHUDWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainHUDWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMainHUDWidget_Statics::ClassParams = {
	&UMainHUDWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UMainHUDWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UMainHUDWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainHUDWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UMainHUDWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMainHUDWidget()
{
	if (!Z_Registration_Info_UClass_UMainHUDWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMainHUDWidget.OuterSingleton, Z_Construct_UClass_UMainHUDWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMainHUDWidget.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UMainHUDWidget>()
{
	return UMainHUDWidget::StaticClass();
}
UMainHUDWidget::UMainHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMainHUDWidget);
UMainHUDWidget::~UMainHUDWidget() {}
// End Class UMainHUDWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMainHUDWidget, UMainHUDWidget::StaticClass, TEXT("UMainHUDWidget"), &Z_Registration_Info_UClass_UMainHUDWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMainHUDWidget), 3982081761U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_1039808338(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Widgets_MainHUD_MainHUDWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
