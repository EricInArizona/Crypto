// Copyright Eric Chauvin 2021.



#include "SPrimes.h"
#include "IntegerMath.h"


SPrimes::SPrimes( void )
{
pArray = new Uint32[arrayLength];
makePrimeArray();
}



SPrimes::~SPrimes( void )
{
delete[] pArray;
}


// The copy constructor.
SPrimes::SPrimes( const SPrimes& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Copy constructor for SPrimes called.\n";
}


Uint32 SPrimes::getBiggestPrime( void )
{
return pArray[arrayLength - 1];
}



Uint32 SPrimes::getPrimeAt( Uint32 where )
{
if( where >= arrayLength )
  throw "getPrimeAt() out of bounds.";

return pArray[where];
}



Uint32 SPrimes::getFirstPrimeFactor(
                                 Uint32 toTest )
{
if( toTest < 2 )
  return 0;

if( toTest == 2 )
  return 2;

if( toTest == 3 )
  return 3;

const Uint64 max = IntegerMath::
                         findULSqrRoot( toTest );
if( max == 0 )
  throw "SPrimes. Max was zero.";

for( Uint32 count = 0; count < arrayLength;
                                         count++ )
  {
  Uint32 testN = pArray[count];
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

Uint32 last = 9;
for( Uint64 testN = 29; ; testN += 2 )
  {
  if( (testN % 3) == 0 )
    continue;

  if( (testN >> 32) != 0 )
    throw "SPrimes. A small prime is a Uint64.";

  // If it has no prime factors then add it.
  if( 0 == getFirstPrimeFactor( (Uint32)testN ))
    {
    pArray[last] = (Uint32)testN;
    last++;
    if( last >= arrayLength )
      return;

    }
  }
}
