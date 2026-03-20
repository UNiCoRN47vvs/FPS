#include "Struct/CurrencyStruct.h"
//-----------------------------------------------------------------------------------------------------------
FCurrency& FCurrency::operator+=(const FCurrency& OtherCurrency)
{
   Sulfur += OtherCurrency.Sulfur;
   return *this;
}
//-----------------------------------------------------------------------------------------------------------
FCurrency& FCurrency::operator*=(const int32 Count)
{
   Sulfur *= Count;
   return *this;
}

//-----------------------------------------------------------------------------------------------------------