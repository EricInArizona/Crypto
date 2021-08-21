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
copy( in );
}



EPoint::EPoint( const Integer& setX,
                const Integer& setY )
{
infin = false;
X.copy( setX );
Y.copy( setY );
}



void EPoint::copy( const EPoint& p )
{
// This might be copying itself, so
// this.x = p.x, which is OK.

infin = p.infin;
X.copy( p.X );
Y.copy( p.Y );
}



bool EPoint::isEqual( const EPoint& in ) const
{
if( infin != in.infin )
  return false;

if( !X.isEqual( in.X ))
  return false;

if( !Y.isEqual( in.Y ))
  return false;

return true;
}



bool EPoint::isConjugate( const EPoint& p,
                          const Integer& modulus,
                          Mod& mod,
                          IntegerMath& intMath )
                                        const
{
if( !X.isEqual( p.X ))
  return false;

Integer temp;
temp.copy( p.Y );
mod.negate( temp, modulus, intMath );
if( !temp.isEqual( Y ))
  throw "Can't happen. Point not on curve.";
//  return false;

return true;
}



// isConjugate() defines the meaning of
// the phrase
// Additive Identity:  P + -P = 0;
// A curve like y^2 = x^3 + ax + b is
// symmetric around the X axis.
// Because -y^2 equals y^2.
// As the curve crosses the X axis it goes
// directly vertical, which would be an
// infinite slope, so to speak.
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



bool EPoint::isOnCurve( const Integer& modulus,
                Mod& mod, IntegerMath& intMath )
{
if( infin )
  return true;

// The curve used in Bitcoin: y^2 = x^3 + 7

// y^2 = x^3 + 7 mod prime.
// x^3 + 7 has to be congruent to a square.

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



void EPoint::add( const EPoint& p,
                  const EPoint& q,
                  const Integer& modulus,
                  Mod& mod,
                  IntegerMath& intMath  )

{
if( modulus.isEqualToUI( coefB ))
  throw "modulus can't be coefB.";

// q + Infinity = q.
if( p.getInfin())
  {
  // If q was infinite too, then it's like
  // zero + zero = zero.
  copy( q );
  return;
  }

if( q.getInfin())
  {
  copy( p );
  return;
  }

if( p.isEqual( q ))
  {
  doubleP( p, modulus, mod, intMath );
  return;
  }

if( p.X.isEqual( q.X ))
  {
  // If it's the same x then the y values
  // can only be the negated values for
  // each other.

  // For testing only.
  if( !p.isConjugate( q, modulus, mod, intMath ))
    {
    throw "Can't happen. !p.isConjugate( q )";
    }

  // Then the two points are in a vertical
  // line, and the line points to something
  // At Infinity.
  setInfin( true );
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

// The X values are different here, but
// the numerator, the difference in y values,
// can equal 0.  So the slope can be zero.

// If p.x is different from q.x can p.y equal
// q.y?  Yes.
// y^2 = x^3 + ax + b is

// p.y - q.y
Integer numerator;
numerator.copy( pY );
mod.subtract( numerator, qY, modulus, intMath );

if( numerator.isZero())
  throw "Yes, the numerator can be zero.";

Integer denom;
denom.copy( pX );
mod.subtract( denom, qX, modulus, intMath );

// The x values are not equal, so denom can't
// be zero, but it can be 1.
Integer slope;
if( denom.isMoreThanUint( 1 ))
  {
  // Avoid calling divide() if denominator is 1
  // because it would just return the
  // numerator if it was 1.

  // This has to do the extended Euclidean
  // algorithm to get the multiplicative inverse.
  mod.divide( slope, numerator, denom,
                           modulus, intMath );
  }
else
  {
  slope.copy( numerator );
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



void EPoint::doubleP( const EPoint& p,
                      const Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath )
{
// coefA and coefB are the coefficients in
// this equation:
// y^2 = x^3 + ax + b
// For Bitcoin a = 0 and b = 7.
// The curve used in Bitcoin: y^2 = x^3 + 7

// if( modulus.isEqualToUI( 2 ))
  // throw "modulus can't be 2.";

// if( modulus.isEqualToUI( 3 ))
  // throw "modulus can't be 3.";

// if( modulus.isEqualToUI( coefB ))
  // throw "modulus can't be coefB.";

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

if( p.getInfin())
  {
  // Infinite + Infinite = Infinite
  copy( p );
  return;
  }

if( pY.isZero() )
  {
  // Then the conjugate to Y would be
  // zero too.
  setInfin( true );
  return;
  }

// The derivative of x^3 + ax is
//                  3x^2 + a
// Multiplying by 3 here means you don't
// want to use base == 3.
// numerator = (3 * (p.x * p.x)) + coefA;

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
  mod.multiplyUL( numerator, 3,
                         modulus, intMath );

  mod.addUL( numerator, coefA, modulus, intMath );
  }

// p.y is not zero here.
// Multiplying by 2 here means you don't
// want to use a base == 2.
Integer denom;
denom.copy( pY );
mod.multiplyUL( denom, 2, modulus, intMath );

Integer slope;
mod.divide( slope, numerator, denom,
            modulus, intMath );

Integer slopeSqr;
slopeSqr.copy( slope );
mod.square( slopeSqr, modulus, intMath );

Integer rightSide;
rightSide.copy( pX );
mod.multiplyUL( rightSide, 2, modulus, intMath );

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



/*
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
*/



/*
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
*/


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
