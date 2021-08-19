// Copyright Eric Chauvin 2021.


#include "EPoint.h"


// Closure: If the result of one of these
// operations makes a point that's not on the
// curve, then it would be an error.
// So the function isOnCurve() tests that.

// Domain parameters: (p, a, b, G, n, h )

// Compressed Point representation.
// The prefix byte, like 0x02 or 0x03 and
// 32 bytes for the X value of the point.
// Of the two possible y values.
// If it's 02 then y is even.
// If it's 03 then y odd.
// 04 is the uncompressed form.

// The prime p:
// p = FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF
//     FFFFFFFF FFFFFFFF FFFFFFFE FFFFFC2F
// p equals 2^256 - 2^32 - 2^9 - 2^8 - 2^7 -
//        2^6 - 2^4 - 1

// The curve E: y^2 = x^3 + ax + b
// a = 0
// b = 7
// G is the Generator point.
// If you have the equation of the curve, and
// the point X, you can find Y.  So you only
// need to define X in what is called the
// compressed format for the representation of
// a point.

// SEC1 Point Representation:
// https://tools.ietf.org/id/
            // draft-jivsov-ecc-compact-05.html
// The 04 means it is uncompressed.
// G = 04
// X =    79BE667E F9DCBBAC 55A06295 CE870B07
//        029BFCDB 2DCE28D9 59F2815B 16F81798

// Y =    483ADA77 26A3C465 5DA4FBFC 0E1108A8
//        FD17B448 A6855419 9C47D08F FB10D4B8

// The order n of G:
// The scalar value for point multiplication
// Q = kP has to be less than this.  In other
// words the private key k has to be less than
// this.
// With ECDSA digital signing, operations are
// mod this N.  Not mod P.

// n = FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE
//     BAAEDCE6 AF48A03B BFD25E8C D0364141

// The function #E( Fp ) means the number of
// points on the curve over the prime p.
// The cofactor is #E( Fp ) / n.
// Since the cofactor is 1, the number of points
// on the curve is equal to the order n.

// Cofactor: h = 01




EPoint::EPoint( void )
{
}


// Copy constructor.
EPoint::EPoint( const EPoint& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't copy EPoint in a copy constructor.";
}



EPoint::EPoint( Integer& setX, Integer& setY )
{
isInfinite = false;
X.copy( setX );
Y.copy( setY );
}


EPoint::EPoint( EPoint& in )
{
copy( in );
}


bool EPoint::isOnCurve( Integer& modulus,
                Mod& mod, IntegerMath& intMath )
{
if( isInfinite )
  return true;

// The curve used in Bitcoin: y^2 = x^3 + 7
Integer left;
left.copy( Y );
mod.square( left, modulus, intMath );

Integer right;
Integer rightTemp;
right.copy( Y );
rightTemp.copy( Y );
mod.multiply( right, rightTemp,
              modulus, intMath );

// Now right is y cubed.

right.addULong( coefB );

if( left.isEqual( right ))
  return true;

return false;
}



void EPoint::copy( EPoint& p )
{
// This might be copying itself, so
// this.x = p.x, which is OK.

isInfinite = p.isInfinite;
X = p.X;
Y = p.Y;
}



bool EPoint::isEqual( EPoint& in )
{
if( isInfinite != in.isInfinite )
  return false;

if( !X.isEqual( in.X ))
  return false;

if( !Y.isEqual( in.Y ))
  return false;

return true;
}


bool EPoint::isConjugate( EPoint& p,
                          Integer& modulus,
                          Mod& mod,
                          IntegerMath& intMath )
{
if( !X.isEqual( p.X ))
  return false;

Integer temp;
temp.copy( p.Y );
mod.negate( temp, modulus, intMath );
if( !temp.isEqual( Y ))
  return false;

return true;
}



// This defines the meaning of the phrase
// Additive Identity:  P + -P = 0;
// A curve like y^2 = x^3 + ax + b is
// symmetric around the X axis.  As the curve
// crosses the X axis it goes directly
// vertical, which would be an infinite
// slope, so to speak.
// The conjugate has the same x coordinate.

// But it has a negated y coordinate.
// So the point and its conjugate are on
// a vertical line.

// If y was 1 and base was 5.
// y = -1 + 5 = 4.
// P + -P = 0.
// 1 + 4 = 0 mod 5.
// y + negate( y ) = 0.

// Also, -4 + 5 is 1.
// So negating 4 makes it 1.



void EPoint::add( EPoint& p, EPoint& q,
                  Integer& modulus,
                  Mod& mod,
                  IntegerMath& intMath  )

{
// if( coefB == modulus )
  // throw "modulus can't be coefB." );

// q + Infinity = q.
if( p.getIsInfinite())
  {
  // If q was infinite too, then it's like
  // zero + zero = zero.
  copy( q );
  return;
  }

if( q.getIsInfinite())
  {
  copy( p );
  return;
  }

if( p.isEqual( q ))
  {
  doubleP( p, modulus, mod, intMath );
  return;
  }

if( p.X.isEqual( q.X )) // But y's are different.
  {
  // If it's the same x then the y values
  // can only be the negated values for
  // each other.

  if( !p.isConjugate( q, modulus, mod, intMath ))
    {
    throw "Can't happen. !p.isConjugate( q )";
    }

  // Then the two points are in a vertical
  // line, and the line points to something
  // At Infinity.
  setIsInfinite( true );
  return;
  }

// One of these points, either p or q, might
// be this same object.  Like P = P + Q.
Integer pX;
Integer pY;
Integer qX;
Integer qY;
pX.copy( p.X );
pY.copy( p.Y );
qX.copy( q.X );
qY.copy( q.Y );

// The X values can be different, but
// the numerator, the difference in y values,
// can equal 0.  So the slope can be zero.

// p.y - q.y
Integer numerator;
numerator.copy( pY );
mod.subtract( numerator, qY, modulus, intMath );

// if( numerator == 0 )
//   Then that's fine.

Integer denom;
denom.copy( pX );
mod.subtract( denom, qX, modulus, intMath );

// The x values are not equal, so denom can't
// be zero, but it can be 1.
Integer slope;
slope.copy( numerator );
Integer one;
one.setToOne();
if( one.paramIsGreater( denom ))
  {
  // Avoid calling divide() if numerator is 1
  // because it would just return the
  // numerator if it was 1.
  mod.divide( slope, numerator, denom,
                           modulus, intMath );
  }

Integer slopeSqr;
slopeSqr.copy( slope );
mod.square( slopeSqr, modulus, intMath );

// x = slopeSqr - p.x - q.x;
Integer tempX;
tempX.copy( slopeSqr );
mod.subtract( tempX, pX, modulus, intMath );
mod.subtract( tempX, qX, modulus, intMath );
X.copy( tempX );

Integer xDelta;
xDelta.copy( pX );
mod.subtract( xDelta, X, modulus, intMath );

// if( xDelta == 0 )
//   Then that's OK.

// y = (slope * xDelta) - p.y;
Integer tempY;
tempY.copy( slope );
mod.multiply( tempY, xDelta, modulus, intMath );
mod.subtract( tempY, pY, modulus, intMath );
Y.copy( tempY );
}



void EPoint::doubleP( EPoint& p,
                      Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath )
{
// coefA and coefB are the coefficients in
// this equation:
// y^2 = x^3 + ax + b
// For Bitcoin a = 0 and b = 7.
// The curve used in Bitcoin: y^2 = x^3 + 7

// This might be doubling itself, so
// this.x would be the same as p.x.

Integer pX;
Integer pY;

pX.copy( p.X );
pY.copy( p.Y );

// Double a point:
// P + P = 2P
// The number 3 comes from the derivative,
// or the slope of the line, of x^3, so it's
// 3x^2.  coefB is a constant and so it's
// not in the derivative.

if( p.getIsInfinite())
  {
  // Infinite + Infinite = Infinite
  copy( p );
  return;
  }

if( pY.isZero() )
  {
  // Then the tangent to the line at P points
  // straight up.
  setIsInfinite( true );
  return;
  }

// The derivative of x^3 + ax is
//                  3x^2 + a
// Multiplying by 3 here means you don't
// want to use base == 3.
// numerator = (3 * (p.x * p.x)) + coefA;

Integer three;
three.setFromULong( 3 );

Integer numerator;
// coefA is zero in Bitcoin.
if( pX.isZero())
  {
  numerator.setFromULong( coefA );
  }
else
  {
  numerator.copy( pX );
  mod.square( numerator, modulus, intMath );
  mod.multiply( numerator, three,
                         modulus, intMath );

  Integer A;
  A.setFromULong( coefA );
  mod.add( numerator, A, modulus, intMath );
  }

// p.y is not zero here.
// Multiplying by 2 here means you don't
// want to use a base == 2.
Integer denom;
Integer two;
denom.copy( pY );
two.setFromULong( 2 );
mod.multiply( numerator, three,
                         modulus, intMath );

// Just shift left.
mod.multiply( denom, two, modulus, intMath );

Integer slope;
mod.divide( slope, numerator, denom,
            modulus, intMath );

Integer slopeSqr;
slopeSqr.copy( slope );
mod.square( slopeSqr, modulus, intMath );

Integer rightSide;
rightSide.copy( pX );
mod.multiply( rightSide, two, modulus, intMath );

// x = slopeSqr - (2 * p.x);

Integer tempX;
tempX.copy( slopeSqr );
mod.subtract( tempX, rightSide, modulus,
                                      intMath );
X.copy( tempX );

// p.x minus the new x.
// y = slope * (p.x - x) - p.y;
Integer xPart;
xPart.copy( pX );
mod.subtract( xPart, X, modulus, intMath );

Integer tempY;
tempY.copy( slope );
mod.multiply( tempY, xPart, modulus, intMath );
Y.copy( tempY );
mod.subtract( Y, pY, modulus, intMath );
}



void EPoint::repeatDoubleP( Integer& twoPower,
                            EPoint p,
                            Integer& modulus,
                            Mod& mod,
                            IntegerMath& intMath )
{
if( twoPower.isZero())
  throw "twoPower is zero.";

// It might be copying itself here.
copy( p );

if( twoPower.isOne()) // 2^0 = 1.
  return; // It's 2^0 times P.

// If twoPower was 2, then shifting it right
// once would leave it at 1, which means
// double it once.
// If it was 4 then shifting it to 2 would
// mean double it twice.
twoPower.shiftRight( 1 );

// If point becomes infinite, or if y becomes
// zero, then it stays infinite.
// while( true )
for( Uint32 count = 0; count < 1000000; count++ )
  {
  EPoint tempThis( X, Y );
  doubleP( tempThis, modulus, mod, intMath );
  X = tempThis.X;
  Y = tempThis.Y;
  twoPower.shiftRight( 1 );
  if( twoPower.isZero())
    return;

  }
}




void EPoint::repeatDoublePByAdd( EPoint& p,
                         Integer& twoPower,
                         Integer& modulus,
                         Mod& mod,
                         IntegerMath& intMath )
{
EPoint originalP( p );

if( twoPower.isZero())
  throw "twoPower is zero.";

// It might be copying itself here.
// This adds something one time.
copy( p );

if( twoPower.isOne())
  return; // It's 2^0 times P = P.

if( !twoPower.isULong())
  throw "twoPower is not a ulong.";

const Uint32 last = (Uint32)twoPower.getAsULong()
                                    - 1;
for( Uint32 count = 0; count < last; count++ )
  {
  EPoint tempThis( X, Y );
  add( tempThis, originalP, modulus, mod,
                                     intMath  );

  X = tempThis.X;
  Y = tempThis.Y;
  }
}


/*
void EPoint::scalarMult( Integer& k,
                         Integer& modulus,
                         long base, long k )
{
// If k = 23
// 23 = 16 + 7 = 10111.
// 23 = 2^4 + 2^2 + 2 + 1
// 23 times P = (2^4 + 2^2 + 2 + 1)P
// 23 times P = 2^4P + 2^2P + 2P + P

EPoint accumP;
accumP.setIsInfinite( true ); // Additive Identiry.
EPoint doubleP( X, Y );

Uint32 oneBit = 1;
//                          63 bits.
for( Uint32 count = 0; count < 63; count++ )
  {
  if( (k.getD( 0 ) & oneBit) != 0 )
    {
    doubleP.repeatDoubleP( base, oneBit, this );
  void repeatDoubleP( Integer& twoPower,
                      EPoint p,
                      Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath );

   accumP.add( base, doubleP, accumP );
    }

  oneBit <<= 1;
  }

copy( accumP );
}
*/


/*
void EPoint::scalarMultByAdd( long base, long k )
                                throws Exception
    {
    EPoint accumP = new EPoint();
    accumP.makeInfinite(); // Additive Identiry.

    for( int count = 0; count < k; count++ )
      {
      accumP.add( base, accumP, this );
      }

    copy( accumP );
    }

*/
