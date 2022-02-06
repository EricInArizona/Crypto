// Copyright Eric Chauvin 2021 - 2022.



#include "TwoDInt64.h"



TwoDInt64::TwoDInt64( void )
{
aR = new Int64[last];
}


TwoDInt64::TwoDInt64( const TwoDInt64& in )
{
aR = new Int64[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Copy constructor for TwoDInt64 called.";
}



TwoDInt64::~TwoDInt64( void )
{
delete[] aR;
}
