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

  // Multiply it for the next bigBase.
  intMath.multiplyUInt( bigBase,
                    sPrimes.getPrimeAt( count ));
  }
}



