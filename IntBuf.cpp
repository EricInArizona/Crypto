// Copyright Eric Chauvin 2021 - 2022.



#include "IntBuf.h"
#include "CastE.h"


IntBuf::IntBuf( void )
{
D = new Int32[CastE::i32ToU64( last )];
}


// Copy constructor.
IntBuf::IntBuf( const IntBuf& in )
{
D = new Int32[CastE::i32ToU64( last )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;


throw "Don't copy IntBuf in a copy constructor.";
}


IntBuf::~IntBuf( void )
{
delete[] D;
}
