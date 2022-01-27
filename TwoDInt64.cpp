// Copyright Eric Chauvin 2021 - 2022.



#include "TwoDInt64.h"



TwoDInt64::TwoDInt64( void )
{
aR = new Int64[last];
}



TwoDInt64::~TwoDInt64( void )
{
delete[] aR;
}
