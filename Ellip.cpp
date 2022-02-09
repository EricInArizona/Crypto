// Copyright Eric Chauvin 2021 - 2022.



#include "Ellip.h"
#include "TimeEC.h"



Ellip::Ellip( void )
{
pArray = new EPoint[last];
}


Ellip::Ellip( const Ellip& in )
{
pArray = new EPoint[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't copy Ellip in copy constructor.";
}


Ellip::~Ellip( void )
{
delete[] pArray;
}



void Ellip::test( FileIO& mainIO )
{
mainIO.appendChars( "Starting ellip test.\n" );

TimeEC t1;

mainTest( mainIO );

TimeEC t2;

Int64 diff = t2.diffSec( t1 );

Str showTime( diff );
mainIO.appendChars( "\nSeconds: " );
mainIO.appendStr( showTime );
mainIO.appendChars( "\n\n" );
mainIO.appendChars( "Finished test.\n" );
}



void Ellip::mainTest( FileIO& mainIO )
{
// Primes have to not be 2 or 3.
// pArray[0] = 2;
// pArray[1] = 3;
// pArray[2] = 5;
// The prime 5 is at index 2.
for( Int32 count = 2; count < 5; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  if( prime == EPoint::coefA )
    continue;

  if( prime == EPoint::coefB )
    continue;

  mainIO.appendChars( "\n\nPrime is: " );
  Str showP( prime );
  mainIO.appendStr( showP );
  mainIO.appendChars( "\n" );

  makeCurvePoints( mainIO, prime );
  }
}



void Ellip::makeCurvePoints( FileIO& mainIO,
                             const Int32 prime )
{
// The curve used in Bitcoin: y^2 = x^3 + 7

mainIO.appendChars( "Making curve points.\n" );

Integer right;
Integer modulus;
modulus.setFromInt24( prime );

for( Int32 x = 0; x < prime; x++ )
  {
  right.setFromInt24( x );
  mod.square( right, modulus, intMath );
  mod.multiplyL( right, x, modulus, intMath );
  // Now right is x cubed.

  if( EPoint::coefA != 1 )
    mod.multiplyL( right, EPoint::coefA,
                             modulus, intMath );

  right.addLong48( EPoint::coefB );

// =====

  // Now find the modular square root.


  // Tonelli Shanks algorithm
  // How does that work?

// Euler's Criterion:
// https://en.wikipedia.org/wiki/Euler%27s_criterion


// "TonelliShanks cannot be used for composite
// moduli: finding square roots modulo composite
// numbers is a computational problem equivalent
// to integer factorization."



  // right is now equal to y squared.
  // What is the square root of right?
  // y^2 = right
  // right = y*2 - z * modulus
  // That's if the square root exists.
  // right has to be congruent to a square,


  // mod.negate( temp, modulus, intMath );

  mainIO.appendChars( "X: " );
  Str showP( x );
  mainIO.appendStr( showP );
  mainIO.appendChars( "\n" );

  // Square root is:
  // Str showP =  intMath.toString10( primeP );
  // mainIO.appendStr( showP );
  // mainIO.appendChars( "\n" );

  }


/*
final int pointArraySize =
                            (int)((base * 2) + 1);
    pointArray = new EPoint[pointArraySize];
    pointArrayLast = 0;

    // Add only one point at Infinity.
    EPoint point = new EPoint();
    point.makeInfinite();
// Set the object in to the array like this?
    pointArray[pointArrayLast] = point;
    pointArrayLast++;

    EPoint accumPoint = new EPoint();
    EPoint dPoint = new EPoint();

    // This is the definition of the phrase
    // "all of the points on a curve".
    // Everything that goes in to pointArray
    // is a point on the curve.
    // Notice that the point at 0,0 might or
    // might not be on the curve, if it works
    // with the equation.  If isOnCurve()
    // returns true.

    for( int x = 0; x < base; x++ )
      {
      long xPart = (x * x * x) + 7;
      xPart = xPart % base;

      for( int y = 0; y < base; y++ )
        {
        point = new EPoint( x, y );
        if( !point.isOnCurve( base ))
          continue;

        if( pointArrayLast >= pointArraySize )
          throw new Exception(
                    "pointArraySize too small." );

        pointArray[pointArrayLast] = point;
        pointArrayLast++;

        if( !accumPoint.isConjugate( base, point ))
          {
          // But it can have a different X value,
          // with y values that might or might not
          // add up to zero.
          // if( accumPoint.y !=
          //   ModNumber.negate( base, point.y ))

          accumPoint.add( base, accumPoint,
                                         point );
          }

        dPoint.copy( point );
        // testDouble( base, dPoint );
        testScalarMult( base, dPoint );

        if( !accumPoint.isOnCurve( base ))
          {
          throw new Exception(
                  "!accumPoint.isOnCurve(). x:" +
                    accumPoint.x + " y: " +
                    accumPoint.y );
          }

        mApp.showStatusAsync( "x: " + x +
                                    " y: " + y );

        mApp.showStatusAsync( "accumPoint.x: " +
            accumPoint.x + " y: " + accumPoint.y );

        mApp.showStatusAsync( "dPoint.x: " +
          dPoint.x + " y: " + dPoint.y );

        }
      }

    // The number of points that are actually
    // on the curve.
    mApp.showStatusAsync( "pointArrayLast: " +
                               pointArrayLast );

*/
}




/*
  public void testDouble( long base,
                                  EPoint dPoint )
                                  throws Exception
    {
    long twoPower = 1; // Two to the 0.
    // twoPower = 2;      Two to the 1.

    for( int count = 0; count < 16; count++ )
      {
      EPoint pTest = new EPoint( dPoint );
      EPoint pTestByAdd = new EPoint( dPoint );

      mApp.showStatusAsync( "twoPower: " +
                                       twoPower );

This twoPower needs to be like 1024 or 2048
or something like that.
twoPowerDoubleP(
Like 2 to the 1024 or something.

      pTest.repeatDoubleP( base, twoPower,
                                      pTest );
      pTestByAdd.repeatDoublePByAdd( base,
                         twoPower, pTestByAdd );

      if( !pTest.isOnCurve( base ))
        {
        throw new Exception(
                "repeatDouble() not on curve." );
        }

      if( !pTestByAdd.isOnCurve( base ))
        {
        throw new Exception(
            "repeatDoubleByAdd() not on curve." );
        }

      if( !pTest.isEqual( pTestByAdd ))
        throw new Exception(
              "!pTest.isEqual( pTestByAdd )" );

      twoPower <<= 1;
      if( twoPower > 0x80 )
        return;

      }
    }
*/



/*
  public void testScalarMult( long base,
                                  EPoint point )
                                  throws Exception
    {
    EPoint pTest = new EPoint();
    EPoint pTestByAdd = new EPoint();

    for( int count = 0; count < 50; count++ )
      {
      // mApp.showStatusAsync(
                         // "Count K: " + count );
      pTest.copy( point );
      pTestByAdd.copy( point );

      pTest.scalarMult( base, count );
      pTestByAdd.scalarMultByAdd( base, count );

      if( !pTest.isOnCurve( base ))
        {
        throw new Exception(
                "scalarMult() not on curve." );
        }

      if( !pTestByAdd.isOnCurve( base ))
        {
        throw new Exception(
            "scalarMultByAdd() not on curve." );
        }

      if( !pTest.isEqual( pTestByAdd ))
        throw new Exception(
          "scalar !pTest.isEqual( pTestByAdd )" );

      }
    }
*/



/*


void EPoint::twoPowerDoubleP(
                        const Uint32 twoPower,
                        const EPoint p,
                        const Integer& modulus,
                        Mod& mod,
                        IntegerMath& intMath )
{
// twoPower is how many times this has to
// be doubled.  If something got doubled
// 32 times it's about 4 billion.
// This has to be doubled like 1024 or 2048
// times or something like that.

if( twoPower == 0 )
  throw "twoPower is zero.";

// It might be copying itself here.
copy( p );

// If point becomes infinite, or if y becomes
// zero, then it stays infinite.

// How many times it has to be doubled.
for( Uint32 count = 0; count < twoPower; count++ )
  {
  EPoint tempThis( X, Y );
  doubleP( tempThis, modulus, mod, intMath );
  X = tempThis.X;
  Y = tempThis.Y;
  }
}



void EPoint::twoPowerByAdd( const EPoint& p,
                      const Uint32 twoPower,
                      const Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath )
{
EPoint originalP( p );

if( twoPower == 0 )
  throw "twoPower is zero.";

// It might be copying itself here.
copy( p );

if( twoPower == 1 )
  return; // It's 2^0 times P = P.

const Uint32 last = twoPower - 1;
for( Uint32 count = 0; count < last; count++ )
  {
  EPoint tempThis( X, Y );
  add( tempThis, originalP, modulus, mod,
                                     intMath  );

  X = tempThis.X;
  Y = tempThis.Y;
  }
}



void EPoint::scalarMult( Integer& k,
                         const Integer& modulus )
{
// If k = 23
// 23 = 16 + 7 = 10111.
// 23 = 2^4 + 2^2 + 2 + 1
// 23 times P = (2^4 + 2^2 + 2 + 1)P
// 23 times P = 2^4P + 2^2P + 2P + P

EPoint accumP;
accumP.setInfin( true ); // Additive Identiry.
EPoint doubleP( X, Y );

Integer kShift;
kShift.copy( k );

UInt32 bitsize = (k.getIndex() + 1) * 32;

Uint32 oneBit = 1;
while( true )
  {
  if( (k.getD( 0 ) & 1) != 0 )
    {


    doubleP.repeatDoubleP( base, oneBit, this );
  void repeatDoubleP( Integer& twoPower,
                      EPoint p,
                      Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath );

   accumP.add( base, doubleP, accumP );

    }

  }

copy( accumP );
}



void EPoint::scalarMultByAdd(
                      const Uint32 k,
                      const Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath )
{
EPoint original( X, Y );
EPoint accumP;
// Make it the Additive Identiry.
accumP.setInfin( true );

for( Uint32 count = 0; count < k; count++ )
  {
  accumP.add( accumP, original, modulus, mod,
                                      intMath  );
  }

copy( accumP );
}

*/
