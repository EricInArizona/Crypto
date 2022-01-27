// Copyright Eric Chauvin 2021 - 2022.



#include "SPrimes.h"
#include "IntegerMath.h"
#include "CastE.h"


SPrimes::SPrimes( void )
{
pArray = new Int32[last];
makePrimeArray();
}



SPrimes::~SPrimes( void )
{
delete[] pArray;
}


SPrimes::SPrimes( const SPrimes& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Copy constructor for SPrimes called.\n";
}


Int32 SPrimes::getBiggestPrime( void )
{
return pArray[last - 1];
}



Int32 SPrimes::getFirstPrimeFactor(
                                Int32 toTest )
{
if( toTest < 2 )
  return 0;

if( toTest == 2 )
  return 2;

if( toTest == 3 )
  return 3;

const Int64 max = IntegerMath::
                         findLSqrRoot( toTest );
if( max == 0 )
  throw "SPrimes. Max was zero.";

for( Int32 count = 0; count < last; count++ )
  {
  Int32 testN = pArray[count];
  if( testN < 1 )
    return 0;

  if( (toTest % testN) == 0 )
    return testN;

  if( testN > max )
    return 0;

  }

return 0;
}




void SPrimes::makePrimeArray( void )
{
pArray[0] = 2;
pArray[1] = 3;
pArray[2] = 5;
pArray[3] = 7;
pArray[4] = 11;
pArray[5] = 13;
pArray[6] = 17;
pArray[7] = 19;
pArray[8] = 23;

Int32 index = 9;
for( Int64 testN = 29; ; testN += 2 )
  {
  if( (testN % 3) == 0 )
    continue;

  if( (testN >> 31) != 0 )
    throw "SPrimes. A small prime is an Int64.";

  // If it has no prime factors then add it.
  if( 0 == getFirstPrimeFactor( CastE::i64ToI32(
                                        testN )))
    {
    pArray[index] = CastE::i64ToI32( testN );
    index++;
    if( index >= last )
      return;

    }
  }
}
