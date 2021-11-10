// Copyright Eric Chauvin 2021.



#include "IntBuf.h"
// #include "Integer.h"


IntBuf::IntBuf( void )
{
D = new Uint32[last];
}


// Copy constructor.
IntBuf::IntBuf( const IntBuf& in )
{
D = new Uint32[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;


throw "Don't copy IntBuf in a copy constructor.";
}


IntBuf::~IntBuf( void )
{
delete[] D;
}
