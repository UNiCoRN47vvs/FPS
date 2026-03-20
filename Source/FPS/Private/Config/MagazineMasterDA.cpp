#include "Config/MagazineMasterDA.h"

TMap<FString, FText> UMagazineMasterDA::GetItemInfo()
{
   TMap<FString, FText> itemInfo = Super::GetItemInfo();

   itemInfo.Add(TEXT("Damage")
      , FText::Format(FText::FromString("{0}{1}{2}")
         , FText::AsNumber(Damage.ValueMin), FText::FromString(TEXT(" - "))
         , FText::AsNumber(Damage.ValueMax)));

   return itemInfo;
}
