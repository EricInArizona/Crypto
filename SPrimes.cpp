// Copyright Eric Chauvin 2021 - 2022.



#include "SPrimes.h"
#include "IntegerMath.h"
#include "CastE.h"


SPrimes::SPrimes( void )
{
pArray = new Int32[last];
makeArray();
}


SPrimes::SPrimes( const SPrimes& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Copy constructor for SPrimes called.\n";
}


SPrimes::~SPrimes( void )
{
delete[] pArray;
}


Int32 SPrimes::getFirstFactor(
                       const Int64 toTest ) const
{
RangeC::test( toTest, 0, 0xFFFFFFFFFFFFL,
        "SPrimes.getFirstFactor() range." );

if( toTest < 2 )
  return 0;

if( toTest == 2 )
  return 2;

if( toTest == 3 )
  return 3;

const Int32 max = CastE::i64ToI32(
            IntegerMath::findLSqrRoot( toTest ));

RangeC::test( max, 1, 0xFFFFFFFFFFFFL,
        "SPrimes. Max was zero." );

for( Int32 count = 0; count < last; count++ )
  {
  Int32 testN = pArray[count];

  if( testN > max )
    return 0;

  if( (toTest % testN) == 0 )
    return testN;

  }

return 0;
}




void SPrimes::makeArray( void )
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
for( Int32 testN = 29; ; testN += 2 )
  {
  if( testN > 0xFFFFFF )
    throw "SPrimes.makeArray() > 24 bits.";

  if( (testN % 3) == 0 )
    continue;

  // If it has no prime factors then add it.
  if( 0 == getFirstFactor( testN ))
    {
    pArray[index] = testN;
    index++;
    if( index >= last )
      return;

    }
  }
}
