// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/FPSPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFPSPlayerController() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
FPS_API UClass* Z_Construct_UClass_AFPSPlayerController();
FPS_API UClass* Z_Construct_UClass_AFPSPlayerController_NoRegister();
FPS_API UClass* Z_Construct_UClass_UDragDropInterface_NoRegister();
FPS_API UClass* Z_Construct_UClass_UMainHUDWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class AFPSPlayerController
void AFPSPlayerController::StaticRegisterNativesAFPSPlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFPSPlayerController);
UClass* Z_Construct_UClass_AFPSPlayerController_NoRegister()
{
	return AFPSPlayerController::StaticClass();
}
struct Z_Construct_UClass_AFPSPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "FPSPlayerController.h" },
		{ "ModuleRelativePath", "FPSPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputMappingContext_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FPSPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MainHUDWidget_MetaData[] = {
		{ "Category", "FPS Player Controller" },
		{ "ModuleRelativePath", "FPSPlayerController.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InputMappingContext;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MainHUDWidget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFPSPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSPlayerController_Statics::NewProp_InputMappingContext = { "InputMappingContext", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSPlayerController, InputMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputMappingContext_MetaData), NewProp_InputMappingContext_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AFPSPlayerController_Statics::NewProp_MainHUDWidget = { "MainHUDWidget", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFPSPlayerController, MainHUDWidget), Z_Construct_UClass_UClass, Z_Construct_UClass_UMainHUDWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MainHUDWidget_MetaData), NewProp_MainHUDWidget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFPSPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSPlayerController_Statics::NewProp_InputMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSPlayerController_Statics::NewProp_MainHUDWidget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFPSPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFPSPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFPSPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AFPSPlayerController_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UDragDropInterface_NoRegister, (int32)VTABLE_OFFSET(AFPSPlayerController, IDragDropInterface), false },  // 3352450350
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFPSPlayerController_Statics::ClassParams = {
	&AFPSPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AFPSPlayerController_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AFPSPlayerController_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFPSPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AFPSPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFPSPlayerController()
{
	if (!Z_Registration_Info_UClass_AFPSPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFPSPlayerController.OuterSingleton, Z_Construct_UClass_AFPSPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFPSPlayerController.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<AFPSPlayerController>()
{
	return AFPSPlayerController::StaticClass();
}
AFPSPlayerController::AFPSPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFPSPlayerController);
AFPSPlayerController::~AFPSPlayerController() {}
// End Class AFPSPlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSPlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFPSPlayerController, AFPSPlayerController::StaticClass, TEXT("AFPSPlayerController"), &Z_Registration_Info_UClass_AFPSPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFPSPlayerController), 696587644U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSPlayerController_h_2706636028(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_FPSPlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
