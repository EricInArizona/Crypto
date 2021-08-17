// Copyright Eric Chauvin 2021.



#include "OneDUint64.h"



OneDUint64::OneDUint64( void )
{
aR = new Uint64[last];
}



OneDUint64::~OneDUint64( void )
{
delete[] aR;
}
