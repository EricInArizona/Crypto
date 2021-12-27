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
// 1             1
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


// I could do this for only the bottom 8 bits
// or mod anything.
// Or to a top index below the current index.
void CrtMath::crt2ToInteger( const Crt2& from,
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

  // Notice that the prime at this count,
  // at this digit, is not in bigBase yet.
  // sPrimes.getPrimeAt( count ));

  intMath.multiplyUInt( bigBase, digit );

  toSet.add( bigBase );
  }
}



void CrtMath::crtToCrt2( const Crt& from,
                         Crt2& toSet,
                         Integer& accum,
                         SPrimes& sPrimes,
                         IntegerMath& intMath )
{
crtToCrt2V1( from, toSet, accum, sPrimes,
                                     intMath );

}




// V1 is version 1 for the most basic
// straight-forward version.
void CrtMath::crtToCrt2V1( const Crt& from,
                           Crt2& toSet,
                           Integer& accum,
                           SPrimes& sPrimes,
                           IntegerMath& intMath )
{
if( from.getD( 0 ) == 1 )
  {
  toSet.setToOne();
  accum.setToOne();
  }
else
  {
  toSet.setToZero();
  accum.setToZero();
  }

Integer bigBase;

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  Uint32 accumDigit = (Uint32)intMath.getMod32(
                                  accum, prime );

  Uint32 testDigit = (Uint32)from.getD( count );

  for( Uint32 countP = 0; countP < prime;
                                      countP++ )
    {
    bigBase.copyFromIntBuf( baseAr[count] );

    // countP might be zero here.
    intMath.multiplyUInt( bigBase, countP );

    Uint32 test = (Uint32)intMath.getMod32(
                                bigBase, prime );
    test += accumDigit;
    test = test % prime;
    if( test == testDigit )
      {
      toSet.setD( (Int32)countP, count );
      // It might add zero here.
      accum.add( bigBase );
      break;
      }
    }
  }
}



void CrtMath::crtToCrt2V2( const Crt& from,
                           Crt2& toSet,
                           Integer& accum,
                           SPrimes& sPrimes,
                           IntegerMath& intMath )
{
// For testing the next V2 version.
Crt accumCrt;

if( from.getD( 0 ) == 1 )
  {
  toSet.setToOne();
  accum.setToOne();
  accumCrt.setToOne();
  }
else
  {
  toSet.setToZero();
  accum.setToZero();
  accumCrt.setToZero();
  }

Integer bigBase;
Crt crtBase;
Crt crtCountP;

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  Uint32 accumDigit = (Uint32)intMath.getMod32(
                                  accum, prime );

/*
  Uint32 accumTest = addForAccum( toSet,
                                   count - 1,
                                  sPrimes );
  if( accumTest != accumDigit )
    throw "accumTest != accumDigit";
*/

  Uint32 testDigit = (Uint32)from.getD( count );

  for( Uint32 countP = 0; countP < prime;
                                      countP++ )
    {
    bigBase.copyFromIntBuf( baseAr[count] );
    crtBase.setFromInteger( bigBase,
                            intMath,
                            sPrimes );

    //    crtBase.copy( baseArCrt[count] )

    // countP might be zero here.
    intMath.multiplyUInt( bigBase, countP );


==== Where am I with this?

    crtCountP.setFromUInt( countP, sPrimes );


    Uint32 test = (Uint32)intMath.getMod32(
                                bigBase, prime );
    test += accumDigit;
    test = test % prime;
    if( test == testDigit )
      {
      toSet.setD( (Int32)countP, count );
      // It might add zero here.
      accum.add( bigBase );

      break;
      }
    }
  }


//  Uint32 baseDigit = (Uint32)
//               baseArCrt[count].getD( count );
//  if( baseDigit == 0 )
//  throw "This never happens. baseDigit == 0.";

//  uint Inverse = (uint)MultInverseArray[
//                           Count, BaseDigit];
// MatchingValue = (MatchingValue * Inverse)
//                                   % Prime;

}



bool CrtMath::test( Integer& t1,
                    IntegerMath& intMath,
                    SPrimes& sPrimes )
{
Crt test1;
test1.setFromInteger( t1, intMath, sPrimes );

Integer accum;

Crt2 test2;
crtToCrt2( test1, test2, accum, sPrimes,
                                    intMath );

if( !accum.isEqual( t1 ))
  return false;

Integer result;

crt2ToInteger( test2, result, intMath );

if( !result.isEqual( t1 ))
  return false;

return true;
}
