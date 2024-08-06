// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/ActorComponents/Interact/InteractComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInteractComponent() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FPS_API UClass* Z_Construct_UClass_UInfoInteractWidget_NoRegister();
FPS_API UClass* Z_Construct_UClass_UInteractComponent();
FPS_API UClass* Z_Construct_UClass_UInteractComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Class UInteractComponent
void UInteractComponent::StaticRegisterNativesUInteractComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UInteractComponent);
UClass* Z_Construct_UClass_UInteractComponent_NoRegister()
{
	return UInteractComponent::StaticClass();
}
struct Z_Construct_UClass_UInteractComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "ActorComponents/Interact/InteractComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/ActorComponents/Interact/InteractComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimerCounter_MetaData[] = {
		{ "Category", "InteractComponent" },
		{ "ModuleRelativePath", "Public/ActorComponents/Interact/InteractComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BPInteractWidget_MetaData[] = {
		{ "Category", "Interact Component" },
		{ "ModuleRelativePath", "Public/ActorComponents/Interact/InteractComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_TimerCounter;
	static const UECodeGen_Private::FClassPropertyParams NewProp_BPInteractWidget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInteractComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UInteractComponent_Statics::NewProp_TimerCounter = { "TimerCounter", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractComponent, TimerCounter), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimerCounter_MetaData), NewProp_TimerCounter_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UInteractComponent_Statics::NewProp_BPInteractWidget = { "BPInteractWidget", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInteractComponent, BPInteractWidget), Z_Construct_UClass_UClass, Z_Construct_UClass_UInfoInteractWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BPInteractWidget_MetaData), NewProp_BPInteractWidget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInteractComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractComponent_Statics::NewProp_TimerCounter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInteractComponent_Statics::NewProp_BPInteractWidget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInteractComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInteractComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInteractComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInteractComponent_Statics::ClassParams = {
	&UInteractComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UInteractComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UInteractComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInteractComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UInteractComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInteractComponent()
{
	if (!Z_Registration_Info_UClass_UInteractComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInteractComponent.OuterSingleton, Z_Construct_UClass_UInteractComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInteractComponent.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UInteractComponent>()
{
	return UInteractComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInteractComponent);
UInteractComponent::~UInteractComponent() {}
// End Class UInteractComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInteractComponent, UInteractComponent::StaticClass, TEXT("UInteractComponent"), &Z_Registration_Info_UClass_UInteractComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInteractComponent), 4279214764U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_1453201457(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_Interact_InteractComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
