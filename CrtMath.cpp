// Copyright Eric Chauvin 2021.



#include "CrtMath.h"



CrtMath::CrtMath( void )
{
baseAr = new IntBuf[
               ProjConst::crtDigitArraySize];
}



CrtMath::CrtMath( const CrtMath& in )
{
baseAr = new IntBuf[
                 ProjConst::crtDigitArraySize];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for CrtMath.\n";
}


CrtMath::~CrtMath( void )
{
delete[] baseAr;
}



void CrtMath::init( IntegerMath& intMath,
                    SPrimes& sPrimes )
{
setupBaseArray( intMath, sPrimes );
}



/*
getInteger() works like this.
It accumulates values like this:

1 +
2 * 1 +  // BigBase times CountPrime at Prime: 3
6 * 2 +  // BigBase times CountPrime at Prime: 5
30 * 3 +  // BigBase times CountPrime at Prime: 7
210 * 8 +  // BigBase times CountPrime at Prime: 11
2,310 * 11 +  // BigBase times CountPrime at Prime: 13
30,030 * 11 +  // BigBase times CountPrime at Prime: 17
510,510 * 17 +  // BigBase times CountPrime at Prime: 19
9,699,690 * 22 +  // BigBase times CountPrime at Prime: 23
223,092,870 * 23 +  // BigBase times CountPrime at Prime: 29
6,469,693,230 * 2 +  // BigBase times CountPrime at Prime: 31
200,560,490,130 * 15 +  // BigBase times CountPrime at Prime: 37
7,420,738,134,810 * 27 +  // BigBase times CountPrime at Prime: 41
304,250,263,527,210 * 28 +  // BigBase times CountPrime at Prime: 43
13,082,761,331,670,030 * 23 +  // BigBase times CountPrime at Prime: 47






These bottom digits are 0 for each prime that gets multiplied by
the base.  So they keep getting one more zero at the bottom of each one.
Then each digit above that is just the whole entire base number mod
the current prime.  (As you can see in SetFromTraditionalInteger()
in the ChineseRemainder.cs file.)
But the ones in BaseModArray only have the zeros at the bottom
on the ones that are smaller than the modulus.

At BaseArray[0] it's 1, 1, 1, 1, 1, .... for all of them.
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 0, 0,
30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 1, 7, 11, 13, 4, 8, 2, 0, 0, 0,
64, 68, 9, 27, 33, 51, 22, 38, 5, 25, 24, 7, 3, 1, 6, 2, 1, 0, 0, 0, 0,
47, 38, 32, 53, 9, 31, 7, 31, 14, 16, 16, 19, 10, 11, 15, 9, 0, 0, 0, 0, 0,
27, 68, 14, 18, 58, 32, 44, 16, 18, 23, 22, 15, 15, 10, 8, 0, 0, 0, 0, 0, 0,
*/



void CrtMath::setupBaseArray( IntegerMath& intMath,
                    SPrimes& sPrimes )
{
// The first few numbers for the base:
// 2             2
// 3             6
// 5            30
// 7           210
// 11        2,310
// 13       30,030
// 17      510,510
// 19    9,699,690
// 23  223,092,870

Integer setBase;
Integer bigBase;

bigBase.setFromUInt( 2 );

setBase.setToOne();
setBase.copyToIntBuf( baseArray[0] );
// setBase.copyFromIntBuf( baseArray[0] );

// Count starts at 1, so it's the prime 3.
// The first time through the loop the base
// is set to 2.
// So BaseArray[0] = 1;
// BaseArray[1] = 2;
// BaseArray[2] = 6;
// BaseArray[3] = 30;
// And so on...
for( Uint32 count = 1; count <
           ProjConst::crtDigitArraySize; count++ )
  {
  setBase.copy( bigBase );
  setBase.copyToIntBuf( baseArray[count] );

  // Multiply it for the next bigBase.
  intMath.multiplyUInt( bigBase,
                    sPrimes.getPrimeAt( count ));
  }
}



