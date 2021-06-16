// Copyright Eric Chauvin 2021.



#include "TwoDUint64.h"



TwoDUint64::TwoDUint64( void )
{
aR = new Uint64[last];
}



TwoDUint64::~TwoDUint64( void )
{
delete[] aR;
}
