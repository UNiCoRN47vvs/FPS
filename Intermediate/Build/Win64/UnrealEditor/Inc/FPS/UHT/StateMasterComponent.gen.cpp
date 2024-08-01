// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPS/Public/ActorComponents/State/StateMasterComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStateMasterComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FPS_API UClass* Z_Construct_UClass_UStateMasterComponent();
FPS_API UClass* Z_Construct_UClass_UStateMasterComponent_NoRegister();
FPS_API UEnum* Z_Construct_UEnum_FPS_EStateName();
UPackage* Z_Construct_UPackage__Script_FPS();
// End Cross Module References

// Begin Enum EStateName
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EStateName;
static UEnum* EStateName_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EStateName.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EStateName.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FPS_EStateName, (UObject*)Z_Construct_UPackage__Script_FPS(), TEXT("EStateName"));
	}
	return Z_Registration_Info_UEnum_EStateName.OuterSingleton;
}
template<> FPS_API UEnum* StaticEnum<EStateName>()
{
	return EStateName_StaticEnum();
}
struct Z_Construct_UEnum_FPS_EStateName_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "Health.Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
		{ "Health.Name", "EStateName::Health" },
		{ "HealthMax.Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
		{ "HealthMax.Name", "EStateName::HealthMax" },
		{ "HealthRegen.Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
		{ "HealthRegen.Name", "EStateName::HealthRegen" },
		{ "ModuleRelativePath", "Public/ActorComponents/State/StateMasterComponent.h" },
		{ "Stamina.Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
		{ "Stamina.Name", "EStateName::Stamina" },
		{ "StaminaMax.Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
		{ "StaminaMax.Name", "EStateName::StaminaMax" },
		{ "StaminaRegen.Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
		{ "StaminaRegen.Name", "EStateName::StaminaRegen" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EStateName::Health", (int64)EStateName::Health },
		{ "EStateName::HealthMax", (int64)EStateName::HealthMax },
		{ "EStateName::HealthRegen", (int64)EStateName::HealthRegen },
		{ "EStateName::Stamina", (int64)EStateName::Stamina },
		{ "EStateName::StaminaMax", (int64)EStateName::StaminaMax },
		{ "EStateName::StaminaRegen", (int64)EStateName::StaminaRegen },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FPS_EStateName_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FPS,
	nullptr,
	"EStateName",
	"EStateName",
	Z_Construct_UEnum_FPS_EStateName_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FPS_EStateName_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FPS_EStateName_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FPS_EStateName_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FPS_EStateName()
{
	if (!Z_Registration_Info_UEnum_EStateName.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EStateName.InnerSingleton, Z_Construct_UEnum_FPS_EStateName_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EStateName.InnerSingleton;
}
// End Enum EStateName

// Begin Class UStateMasterComponent
void UStateMasterComponent::StaticRegisterNativesUStateMasterComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UStateMasterComponent);
UClass* Z_Construct_UClass_UStateMasterComponent_NoRegister()
{
	return UStateMasterComponent::StaticClass();
}
struct Z_Construct_UClass_UStateMasterComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//-----------------------------------------------------------------------------------------------------------\n" },
#endif
		{ "IncludePath", "ActorComponents/State/StateMasterComponent.h" },
		{ "ModuleRelativePath", "Public/ActorComponents/State/StateMasterComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStateMasterComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UStateMasterComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FPS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStateMasterComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStateMasterComponent_Statics::ClassParams = {
	&UStateMasterComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UStateMasterComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UStateMasterComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UStateMasterComponent()
{
	if (!Z_Registration_Info_UClass_UStateMasterComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStateMasterComponent.OuterSingleton, Z_Construct_UClass_UStateMasterComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UStateMasterComponent.OuterSingleton;
}
template<> FPS_API UClass* StaticClass<UStateMasterComponent>()
{
	return UStateMasterComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UStateMasterComponent);
UStateMasterComponent::~UStateMasterComponent() {}
// End Class UStateMasterComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EStateName_StaticEnum, TEXT("EStateName"), &Z_Registration_Info_UEnum_EStateName, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2250722387U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UStateMasterComponent, UStateMasterComponent::StaticClass, TEXT("UStateMasterComponent"), &Z_Registration_Info_UClass_UStateMasterComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStateMasterComponent), 1432492798U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_632871962(TEXT("/Script/FPS"),
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_FPS_Source_FPS_Public_ActorComponents_State_StateMasterComponent_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
