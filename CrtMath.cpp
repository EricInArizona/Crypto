// Copyright Eric Chauvin 2021.



#include "CrtMath.h"



CrtMath::CrtMath( void )
{
baseAr = new IntBuf[last];
baseArCrt = new Crt[last];
}



CrtMath::CrtMath( const CrtMath& in )
{
baseAr = new IntBuf[last];
baseArCrt = new Crt[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for CrtMath.\n";
}


CrtMath::~CrtMath( void )
{
delete[] baseAr;
delete[] baseArCrt;

}



void CrtMath::init( IntegerMath& intMath,
                    SPrimes& sPrimes )
{
setupBaseArray( intMath, sPrimes );
}



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

Integer bigBase;

bigBase.setToOne();
bigBase.copyToIntBuf( baseAr[0] );
baseArCrt[0].setToOne();

// setBase.copyFromIntBuf( baseAr[0] );

bigBase.setFromUInt( 2 );

// Count starts at 1, so it's the prime 3.
// The first time through the loop the base
// is set to 2.
// So BaseAr[0] = 1;
// BaseAr[1] = 2;
// BaseAr[2] = 6;
// BaseAr[3] = 30;
// And so on...

for( Uint32 count = 1; count < last; count++ )
  {
  bigBase.copyToIntBuf( baseAr[count] );
  baseArCrt[count].setFromInteger( bigBase,
                                   intMath,
                                   sPrimes );

  // Multiply it for the next bigBase.
  intMath.multiplyUInt( bigBase,
                    sPrimes.getPrimeAt( count ));
  }
}



void CrtMath::crt2ToInteger( Crt2& from,
                             Integer& toSet,
                             IntegerMath& intMath )
{
// Set it to one or zero to start.
toSet.setFromUInt( (Uint32)from.getD( 0 ));

Integer bigBase;

for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 digit = (Uint32)from.getD( count );
  if( digit == 0 )
    continue;

  bigBase.copyFromIntBuf( baseAr[count] );
  intMath.multiplyUInt( bigBase, digit );
  toSet.add( bigBase );
  }
}



void CrtMath::crtToCrt2( Crt& from, Crt2& toSet,
                         SPrimes& sPrimes )
{
Integer accum;

// It's either zero or one.
if( from.getD( 0 ) == 0 )
  toSet.setToZero();
else
  toSet.setToOne();

Integer bigBase;
bigBase.setFromUInt( 2 );

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );

  // uint AccumulateDigit = (uint)CRTAccumulate.GetDigitAt( Count );

  Uint32 testDigit = (Uint32)from.getD( count );

/*
      uint BaseDigit = (uint)CRTBaseArray[Count].GetDigitAt( Count );
      if( BaseDigit == 0 )
        throw( new Exception( "This never happens. BaseDigit == 0." ));

      uint MatchingValue = CRTInputTestDigit;
      if( MatchingValue < AccumulateDigit )
        MatchingValue += Prime;

      MatchingValue -= AccumulateDigit;
      uint Inverse = (uint)MultInverseArray[Count, BaseDigit];
      MatchingValue = (MatchingValue * Inverse) % Prime;
      // This loop shows how it tries to find a matching
      // CountPrime.  It is for bug testing.  It could
      // just use the MatchingValue without using the
      // loop to verify that it's valid.  But it shows
      // clearly how it is trying to find a number that
      // matches up with the CRTInput digit.


  for( Uint32 countP = 0; countP < prime;
                                       countP++ )
    {
        uint ToTestInt = BaseDigit;
        ToTestInt *= CountPrime;
        ToTestInt += AccumulateDigit;
        ToTestInt %= Prime;
        if( CRTInputTestDigit == ToTestInt )
          {
          if( MatchingValue != CountPrime )
            {
            throw( new Exception( "Bug: MatchingValue is not right." ));
            }

          // Notice that the first time through this loop it's zero, so the
          // base part isn't added if it's already congruent to the Value.
          // So even though it goes all the way up through the DigitsArray,
          // this whole thing could add up to a small number like 7.

          ToTestForTraditionalInteger.Copy( BigBase );
          CRTToTestForTraditionalInteger.Copy( CRTBaseArray[Count] );
          IntMath.MultiplyUInt( ToTestForTraditionalInteger, CountPrime );
          CRTToTestForTraditionalInteger.Multiply( NumbersArray[CountPrime] );
          Accumulate.Add( ToTestForTraditionalInteger );
          CRTAccumulate.Add( CRTToTestForTraditionalInteger );
          break;
          }


*/
  }

}
