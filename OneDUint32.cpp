// Copyright Eric Chauvin 2021.



#include "OneDUint32.h"



OneDUint32::OneDUint32( void )
{
aR = new Uint32[last];
}



OneDUint32::~OneDUint32( void )
{
delete[] aR;
}
