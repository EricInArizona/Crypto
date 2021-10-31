// Copyright Eric Chauvin 2021.



#include "IntBuf.h"
// #include "Integer.h"


IntBuf::IntBuf( void )
{
last = 0;
}


IntBuf::IntBuf( const Uint32 setSize )
{
last = setSize;
D = new Uint32[last];
}



// Copy constructor.
IntBuf::IntBuf( const IntBuf& in )
{
last = 0;

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't copy IntBuf in a copy constructor.";
}


IntBuf::~IntBuf( void )
{
delete[] D;
}
