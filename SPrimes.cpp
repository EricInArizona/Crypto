// Copyright Eric Chauvin 2021.


#include "SPrimes.h"
#include "IntegerMath.h"


SPrimes::SPrimes( void )
{
pArray = new Uint64[arrayLength];
makePrimeArray();
}


// The copy constructor.
SPrimes::SPrimes( const SPrimes& obj )
{
throw "Copy constructor for SPrimes called.\n";
}


Uint64 SPrimes::getBiggestPrime( void )
{
return pArray[arrayLength - 1];
}



Uint32 SPrimes::getPrimeAt( Uint32 where )
{
if( where >= arrayLength )
  return 0;

return pArray[where];
}



Uint64 SPrimes::getFirstPrimeFactor(
                                 Uint64 toTest )
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
  throw "Max was zero.";

for( Uint32 count = 0; count < arrayLength;
                                         count++ )
  {
  Uint64 testN = pArray[count];
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

  // If it has no prime factors then add it.
  if( 0 == getFirstPrimeFactor( testN ))
    {
    pArray[last] = testN;
    last++;
    if( last >= arrayLength )
      return;

    }
  }
}
