// Copyright Eric Chauvin 2021 - 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#include "../CppBase/TimeApi.h"

#include "Ellip.h"
#include "../CryptoBase/TonelliShanks.h"



Ellip::Ellip( void )
{
pArray = new EPoint[arraySize];
baseArray = new EPoint[arraySize];
}


Ellip::Ellip( const Ellip& in )
{
pArray = new EPoint[arraySize];
baseArray = new EPoint[arraySize];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't copy Ellip in copy constructor.";
}



Ellip::~Ellip( void )
{
delete[] pArray;
delete[] baseArray;
}



void Ellip::test( void )
{
// mainIO.appendChars( "Starting ellip test.\n" );

// TimeApi t1;

mainTest();

// TimeApi t2;

// Int64 diff = t2.diffSec( t1 );

// Str showTime( diff );
// mainIO.appendChars( "\nSeconds: " );
// mainIO.appendStr( showTime );
// mainIO.appendChars( "\n\n" );
// mainIO.appendChars( "Finished test.\n" );
}




void Ellip::mainTest( void )
{
// Primes have to not be 2 or 3.
// pArray[0] = 2;
// pArray[1] = 3;
// pArray[2] = 5;
// The prime 5 is at index 2.
for( Int32 count = 2; count < 50; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  if( prime == EPoint::coefA )
    continue;

  if( prime == EPoint::coefB )
    continue;

  // mainIO.appendChars( "\n\nPrime is: " );
  // Str showP( prime );
  // mainIO.appendStr( showP );
  // mainIO.appendChars( "\n" );

  makeCurvePoints( prime );
  testAddPoints();
  testDoublePoints();
  }
}




bool Ellip::crudeModRoot( Integer& result,
                          Integer& right )
{
result.setToZero();

if( right.isZero())
  return true;

Integer z;
Integer sum;
Integer sqrRoot;

z.setToZero();
for( Int32 count = 0; count < 100000; count++ )
  {
  // right + (z * modulus) = y*2
  sum.copy( z );
  intMath.multiply( sum, modulus );
  sum.add( right );
  if( intMath.squareRoot( sum, sqrRoot ))
    {
    Integer test;
    test.copy( sqrRoot );
    mod.square( test, modulus, intMath );
    if( !test.isEqual( right ))
      throw "crudeModRoot is not right.";

    result.copy( sqrRoot );
    return true;
    }


  z.increment();
  if( modulus.paramIsGreaterOrEq( z ))
    return false;

  }

return false;
}




void Ellip::makeCurvePoints( const Int32 prime )
{
last = 0;

// The curve used in Bitcoin: y^2 = x^3 + 7

// If the prime made it so that x^3 + 7 = prime, which is
// zero, then y^2 would equal zero.  So y == 0 could be
// on the curve.


// mainIO.appendChars( "Making curve points.\n" );

Integer right;

modulus.setFromInt24( prime );

Integer y;
Integer y2;
Integer xVal;

for( Int32 x = 0; x < prime; x++ )
  {
  right.setFromInt24( x );

  mod.square( right, modulus, intMath );

  mod.multiplyL( right, x, modulus, intMath );
  // Now right is x cubed.

  // if( EPoint::coefA != 0 )
  //   then add that ax part.

  mod.addL( right, EPoint::coefB, modulus, intMath );

  // right + (z * modulus) = = y^2

  // That's if the square root exists.

  // mainIO.appendChars( "Right: " );
  // Str showR( right.getD( 0 ) );
  // mainIO.appendStr( showR );
  // mainIO.appendChars( "\n" );

  Integer rootTonelli;

  bool TonelliOK = TonelliShanks::modRoot( right,
                        rootTonelli,
                        modulus, intMath, mod );
/*
  if( !crudeModRoot( y, right ))
    {
    if( TonelliOK )
      throw "Tonelli disagrees.";

    continue;
    }
*/

  if( !TonelliOK )
    continue; // Square root doesn't exist.
    // throw "Tonelli disagrees on second one.";

  y.copy( rootTonelli );

  xVal.setFromInt24( x );
  pArray[last].setValues( xVal, y );

  if( !pArray[last].isOnCurve( modulus, mod, intMath ))
    throw "This point is not on the curve.";

  last++;

  if( last >= arraySize )
    throw "The ellip array is too small.";

  if( !y.isZero())
    {
    y2.copy( y );
    mod.negate( y2, modulus, intMath );

    if( !( y.isEqual( rootTonelli ) ||
           y2.isEqual( rootTonelli )))
      throw "Tonelli disagrees on value.";

    pArray[last].setValues( xVal, y2 );
    if( !pArray[last].isOnCurve( modulus, mod, intMath ))
      throw "This second point is not on the curve.";

    last++;
    }

  // mainIO.appendChars( "X: " );
  // Str showP( x );
  // mainIO.appendStr( showP );
  // mainIO.appendChars( "\n" );

  // Square root is:
  // mainIO.appendChars( "Y: " );
  // Str showY =  intMath.toString10( y );
  // mainIO.appendStr( showY );
  // mainIO.appendChars( "\n\n" );
  }
}



void Ellip::testAddPoints( void )
{
// mainIO.appendChars( "testAddPoints()\n" );

EPoint testP;

for( Int32 count = 0; (count + 1) < last; count++ )
  {
  testP.add( pArray[count], pArray[count + 1], modulus,
                                           mod, intMath  );

  if( !testP.isOnCurve( modulus, mod, intMath ))
        throw "The added points don't add up.";

  }
}




void Ellip::testDoublePoints( void )
{
// mainIO.appendChars( "testDoublePoints()\n" );

EPoint testP;

for( Int32 count = 0; count < last; count++ )
  {
  testP.doubleP( pArray[count], modulus, mod, intMath  );

  if( !testP.isOnCurve( modulus, mod, intMath ))
        throw "The doubled points aren't right.";

  }
}





/*
void EPoint::scalarMult( Integer& k,  const Integer& modulus )
{
// If k = 23
// 23 = 16 + 7 = 0b10111.
// 23 = 2^4 + 2^2 + 2 + 1
// 23 times P = (2^4 + 2^2 + 2 + 1)P
// 23 times P = 2^4P + 2^2P + 2P + P

EPoint accumP;
accumP.setInfin( true ); // Additive Identiry.
EPoint toDouble( X, Y );

Integer kShift;
kShift.copy( k );

Int32 bitsize = (k.getIndex() + 1) * 24;

Int32 oneBit = 1;
while( true )
  {
  if( (k.getD( 0 ) & 1) != 0 )
    {

    toDouble.repeatDoubleP( base, oneBit, this );
  void repeatDoubleP( Integer& twoPower,
                      EPoint p,
                      Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath );

    accumP.add( base, toDouble, accumP );

    }

  }


copy( accumP );
}

*/



// Set up the bases just like in Exponents.cpp.


void Ellip::setupBases( const EPoint p )
{
EPoint toDouble;
toDouble.copy( p );

// If point becomes infinite, or if y becomes
// zero, then it stays infinite.

for( Int32 count = 0; count < arraySize; count++ )
  {
  toDouble.doubleP( toDouble, modulus, mod, intMath );
  baseArray[count].copy( toDouble );
  }
}
