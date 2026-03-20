#include "Config/PartMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
TMap<FString, FText> UPartMasterDA::GetItemInfo()
{
   TMap<FString, FText> itemInfo = Super::GetItemInfo();

   itemInfo.Add(TEXT("Damage")
      , FText::Format(FText::FromString("{0}{1}{2}")
      , FText::AsNumber(Damage.ValueMin), FText::FromString(TEXT(" - "))
      , FText::AsNumber(Damage.ValueMax)));

   itemInfo.Add(TEXT("Attack Speed"), FText::AsNumber(AttackSpeed));

   itemInfo.Add(TEXT("Firing Mode"), StaticEnum<EFiringMode>() ? StaticEnum<EFiringMode>()->GetDisplayNameTextByValue(static_cast<int32>(FiringMode)) : FText::FromString(TEXT("Invalid")));
   
    return itemInfo;
}
//-----------------------------------------------------------------------------------------------------------
FStatRange UPartMasterDA::GetItemDamage()
{
    return Damage;
}
