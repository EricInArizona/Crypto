// Copyright Eric Chauvin 2021.



#include "Ellip.h"
#include "TimeEC.h"



Ellip::Ellip( void )
{
pArray = new EPoint[Ellip::pArrayLength];
}


// Copy constructor.
Ellip::Ellip( const Ellip& in )
{
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

Str showTime( (Uint64)diff );
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
for( Uint32 count = 2; count < 5; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
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
                             const Uint32 prime )
{
// The curve used in Bitcoin: y^2 = x^3 + 7

mainIO.appendChars( "Making curve points.\n" );

for( Uint32 x = 0; x < prime; x++ )
  {
  mainIO.appendChars( "Prime: \n" );
  }

/*
final int pointArraySize =
                            (int)((base * 2) + 1);
    pointArray = new EPoint[pointArraySize];
    pointArrayLast = 0;

    // Add only one point at Infinity.
    EPoint point = new EPoint();
    point.makeInfinite();
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
