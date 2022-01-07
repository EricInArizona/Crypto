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

throw "Don't use copy constructor for MultInv.";
}


MultInv::~MultInv( void )
{
delete[] u32Arrays;
}



Uint32 MultInv::calcMultInv( const Uint32 prime,
                             const Uint32 test )
{
for( Uint32 count = 1; count < prime; count++ )
  {
  Uint32 check = test * count;
  check = check % prime;
  if( check == 1 )
    return count;

  }

return 0;
}



void MultInv::init( SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  u32Arrays[count].setSize( prime );
  u32Arrays[count].setVal( 0, 0 );

  for( Uint32 countP = 1; countP < prime;
                                    countP++ )
    {
    Uint32 inv = calcMultInv( prime, countP );
    u32Arrays[count].setVal( countP, inv );
    }
  }
}
