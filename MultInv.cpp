// Copyright Eric Chauvin 2022.



#include "MultInv.h"
#include "CastE.h"



MultInv::MultInv( void )
{
i32Arrays = new Int32Array[CastE::i32ToU64(
                                      last )];
}


MultInv::MultInv( const MultInv& in )
{
i32Arrays = new Int32Array[CastE::i32ToU64(
                                      last )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for MultInv.";
}


MultInv::~MultInv( void )
{
delete[] i32Arrays;
}



Int32 MultInv::calcMultInv( const Int32 prime,
                            const Int32 test )
{
for( Int32 count = 1; count < prime; count++ )
  {
  Int32 check = test * count;
  check = check % prime;
  if( check == 1 )
    return count;

  }

return 0;
}



void MultInv::init( const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  i32Arrays[count].setSize( prime );
  i32Arrays[count].setVal( 0, 0 );

  for( Int32 countP = 1; countP < prime;
                                    countP++ )
    {
    Int32 inv = calcMultInv( prime, countP );
    i32Arrays[count].setVal( countP, inv );
    }
  }
}
