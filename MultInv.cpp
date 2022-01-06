// Copyright Eric Chauvin 2022.



#include "MultInv.h"



MultInv::MultInv( void )
{
u32Arrays = new Uint32Array[last];
}


MultInv::MultInv( const MultInv& in )
{
u32Arrays = new Uint32Array[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for MultInv.\n";
}


MultInv::~MultInv( void )
{
delete[] u32Arrays;
}
