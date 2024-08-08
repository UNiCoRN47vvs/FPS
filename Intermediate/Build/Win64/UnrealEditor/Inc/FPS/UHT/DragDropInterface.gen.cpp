// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/Interfaces/DragDropInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDragDropInterface() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
FPS_API UClass* Z_Construct_UClass_UDragDropInterface();
FPS_API UClass* Z_Construct_UClass_UDragDropInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Interface UDragDropInterface
void UDragDropInterface::StaticRegisterNativesUDragDropInterface()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDragDropInterface);
UClass* Z_Construct_UClass_UDragDropInterface_NoRegister()
{
	return UDragDropInterface::StaticClass();
}
struct Z_Construct_UClass_UDragDropInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/DragDropInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IDragDropInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UDragDropInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDragDropInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDragDropInterface_Statics::ClassParams = {
	&UDragDropInterface::StaticClass,
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
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDragDropInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UDragDropInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UDragDropInterface()
{
	if (!Z_Registration_Info_UClass_UDragDropInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDragDropInterface.OuterSingleton, Z_Construct_UClass_UDragDropInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDragDropInterface.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UDragDropInterface>()
{
	return UDragDropInterface::StaticClass();
}
UDragDropInterface::UDragDropInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UDragDropInterface);
UDragDropInterface::~UDragDropInterface() {}
// End Interface UDragDropInterface

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_DragDropInterface_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDragDropInterface, UDragDropInterface::StaticClass, TEXT("UDragDropInterface"), &Z_Registration_Info_UClass_UDragDropInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDragDropInterface), 3352450350U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_DragDropInterface_h_1277928836(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_DragDropInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_Interfaces_DragDropInterface_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
