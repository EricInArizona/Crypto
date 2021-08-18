// Copyright Eric Chauvin 2021.



#include "Mod.h"
#include "Division.h"



Mod::Mod( void )
{
}


// Copy constructor.
Mod::Mod( const Mod& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't copy Mod in a copy constructor.";
}



void Mod::makeExact( Integer& exact,
                     Integer& modulus,
                     IntegerMath& intMath )
{
// Most of the time the math is not exact,
// like in the modular exponentiation function
// toPower().  It leaves some small
// multiple of the modulus.  So this gets rid
// of that small left over multiple of the
// modulus.

Integer quotient;
Integer remainder;

Division::divide( exact, modulus,
                  quotient, remainder, intMath );

exact.copy( remainder );
}



// This is the standard modular power algorithm
// that you could find in any standard textbook,
// or on Wikipedia, but its use of the new
// modular reduction algorithm is new (in 2015).

// x^n = (x^2)^((n - 1)/2) if n is odd.
// x^n = (x^2)^(n/2)       if n is even.
void Mod::toPower( // FileIO& mainIO,
                        Integer& result,
                        Integer& exponent,
                        Integer& modulus,
                        IntegerMath& intMath )
{
if( result.isZero())
  {
  // mainIO.appendChars(
  //            "toPower() is zero at top.\n" );

  return; // With Result still zero.
  }

if( result.isEqual( modulus ))
  {
  // It is congruent to zero % ModN.
  // mainIO.appendChars(
  //       "Congruent to zero in toPower().\n" );
  result.setToZero();
  return;
  }

// Result is not zero at this point.
if( exponent.isZero() )
  {
  // mainIO.appendChars(
  //       "Exponent is zero in toPower().\n" );
  result.setToOne();
  return;
  }

Integer quotient;
Integer remainder;

if( modulus.paramIsGreater( result ))
  {
  Division::divide( result, modulus,
                          quotient, remainder,
                          intMath );
  result.copy( remainder );
  }


if( exponent.isOne())
  {
  // mainIO.appendChars(
  //      "Exponent is one in toPower().\n" );
  // Result stays the same.
  return;
  }

Integer xForModPower;
Integer exponentCopy;
Integer tempForModPower;

xForModPower.copy( result );
exponentCopy.copy( exponent );
// Uint32 testIndex = 0;

result.setToOne();

// For each bit.
while( true )
  {
  if( (exponentCopy.getD( 0 ) & 1) == 1 )
    {
    intMath.multiply( result, xForModPower );

    // tempForModPower is the result of this
    // reduce() operation.
    numbSys.reduce( tempForModPower,
                    result, modulus, intMath );
    result.copy( tempForModPower );
    }

  exponentCopy.shiftRight( 1 ); // Divide by 2.
  if( exponentCopy.isZero())
    break;

  // Square it.
  // intMath.multiply( xForModPower, xForModPower );
  intMath.square( xForModPower );

  numbSys.reduce( tempForModPower,
                xForModPower, modulus, intMath );
  xForModPower.copy( tempForModPower );
  }

// When reduce() gets called it multiplies a base
// number by a uint sized digit.  So that can
// make the result one digit bigger than the
// modulus.  Then when they are added up
// you can get carry bits that can make it a
// little bigger.

Int32 howBig = (Int32)result.getIndex() -
               (Int32)modulus.getIndex();
// if( howBig > 1 )
  // throw "This does happen.";

if( howBig > 2 )
  throw "This never happens yet. howBig.";

numbSys.reduce( tempForModPower, result,
                            modulus, intMath );
result.copy( tempForModPower );

// Notice that this Divide() is done once.
// Not a thousand or two thousand times.
makeExact( result, modulus, intMath );
}




/*
Java code:

  public static void verifyInBaseRange(
                                   long base,
                                   long toCheck )
                                 throws Exception
    {
    if( toCheck < 0 )
      throw new Exception( "verifyInBaseRange()
                               exception 1." );

    if( toCheck >= base )
      throw new Exception( "verifyInBaseRange()
                                 exception 2." );

    }


  public static void verifyMoreThanZero(
                                   long toCheck )
                                 throws Exception
    {
    if( toCheck <= 0 )
      throw new Exception(
                      "verifyMoreThanZero()." );

    }



  public static long add( long base, long in,
                                     long toAdd )
                                  throws Exception
    {
    verifyInBaseRange( base, toAdd );
    verifyInBaseRange( base, in );

    long result = in + toAdd;
    result = result % base;
    return result;
    }


  public static long negate( long base, long in )
                               throws Exception
    {
    // If y was 1 and base was 5.
    // 1 + (-1) = 0;
    // y = -1 + 5 = 4.
    // 1 + 4 = 0 mod 5.
    // The definition of the word 'negate':
    // y + negate( y ) = 0.

    // If I was using a table (array) I could use
    // only symbols from within the range zero
    // to base - 1.  But I use negative numbers
    // and numbers that are more than or equal
    // to base in order to do the math.
    // Like this assignment: result = -in.
    // I have to go outside of the set of numbers
    // in order to find the right numbers that
    // are inside of the set.

    verifyInBaseRange( base, in );
    long result = -in;
    result += base;
    return result;
    }



  public static long subtract( long base, long in,
                               long toSub )
                               throws Exception
    {
    verifyInBaseRange( base, in );
    verifyInBaseRange( base, toSub );
    long result = in - toSub;
    if( result < 0 )
      result += base;

    result = result % base;
    return result;
    }



  public static long multiply( long base, long in,
                               long toMul )
                               throws Exception
    {
    verifyInBaseRange( base, in );
    verifyInBaseRange( base, toMul );
    long result = in * toMul;
    result = result % base;
    return result;
    }



  public static long square( long base, long in )
                               throws Exception
    {
    verifyInBaseRange( base, in );
    long result = in * in;
    result = result % base;
    return result;
    }



  public static long divide( long base,
                             long numerator,
                             long divisor )
                             throws Exception
    {
    verifyInBaseRange( base, divisor );
    verifyInBaseRange( base, numerator );
    verifyMoreThanZero( divisor );

    if( numerator == 0 )
      return 0;

    if( divisor == 1 )
      {
      // num / denom = result
      // 1 / 1 = 1
      // num * denom^-1 = result
      // num * 1 = num
      return numerator;
      }

    // The definition of multiplicative inverse:
    // soAndSo * multInverse == 1.
    // You can't have a multiplicative inverse
    // of zero.  0 * anything = 0.  So it can't
    // equal 1.

    // base should be a prime, so the GCD with
    // divisor is 1.

    // Get the multiplicative inverse.
    long inv = Euclid.multInverse( base, divisor );
    // Returns 0 if they had a GCD > 1.
    if( inv == 0 )
      {
      throw new Exception(
             "Inv == 0 in divide(). " +
                divisor + ", " + base );
      }

    verifyInBaseRange( base, inv );

    long result = numerator * inv;
    result = result % base;
    return result;
    }

Java code.
*/
