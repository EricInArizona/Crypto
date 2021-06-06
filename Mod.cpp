// Copyright Eric Chauvin 2015 - 2021.



#include "Mod.h"
#include "Division.h"


// If you said that something is a base-10
// number or a base-16 (hexadecimal) number,
// that number system is based on multiples of
// that base.  Base-10 numbers are based on
// 10, 100, 1000... and so on.
// When I use the word 'base' here, I mean
// like if something is equal to 3 mod 7,
// then 7 is the base number.
// See the reduce() function.



Mod::Mod( void )
{

}


// Copy constructor.
Mod::Mod( const Mod& in )
{
throw "Don't copy Mod in a copy constructor.";
}


Mod::~Mod( void )
{

}


void Mod::setupBaseArray( Integer& setBase,
                          IntegerMath& intMath )
{
currentBase.copy( setBase );

Integer base2;
base2.setFromULong( 256 ); // 0x100
intMath.multiplyUInt( base2, 256 ); // 0x10000
intMath.multiplyUInt( base2, 256 ); // 0x1000000
intMath.multiplyUInt( base2, 256 );
// Now it is: 0x1 0000 0000

// 0x100000000 is the
// base of this number system.

Integer baseValue;
Integer quotient;
Integer remainder;

baseValue.setFromULong( 1 );

for( Uint32 column = 0; column <
             Integer::digitArraySize; column++ )
  {
  Division::divide( baseValue, currentBase,
                    quotient, remainder,
                    intMath );

  baseAr[column].copy( remainder );

  // This would need a full size baseValue.
  // Not mod the remainder.
  // quotientAr[column].copy( quotient );

  // Done at the bottom for the next round of
  // the loop.
  baseValue.copy( remainder );
  intMath.multiply( baseValue, currentBase );
  }
}



void Mod::makeExact( Integer& exact,
                          IntegerMath& intMath )
{
// Most of the time the math is not exact,
// like in the modular exponentiation function
// modularPower().  It leaves some small
// multiple of currentBase.  So this gets rid
// of that small left over multiple of
// currentBase.

Integer quotient;
Integer remainder;

Division::divide( exact, currentBase,
                  quotient, remainder, intMath );

exact.copy( remainder );
}



Uint32 Mod::reduce( Integer& result,
                           Integer& toReduce,
                           IntegerMath& intMath )
{
if( toReduce.paramIsGreater( currentBase ))
  {
  result.copy( toReduce );
  return result.getIndex();
  }

result.setToZero();

Uint32 topOfToReduce = toReduce.getIndex() + 1;
Uint32 highestCopyIndex = currentBase.getIndex();

Integer accumBase;

// Those parts that are less than the base are
// still at some power of two.

result.copyUpTo( toReduce, highestCopyIndex - 1 );

// But from here up they have to be added
// up individually.
Uint32 biggestIndex = 0;
for( Uint32 count = highestCopyIndex; count <
                        topOfToReduce; count++ )
  {
  // The size of the numbers in baseAr are all
  // less than the size of currentBase.
  // This multiplication by a uint is with a
  // number that is not bigger than currentBase.
  // Compare this with the two full muliply()
  // calls done on each digit of the quotient
  // in LongDivide3().

  // accumBase is set to a new value here.
  Uint32 checkIndex = intMath.
            multiplyUIntFromCopy( accumBase,
            baseAr[count],
            toReduce.getD( count ));

  if( checkIndex > biggestIndex )
    biggestIndex = checkIndex;

  result.add( accumBase );
  }

return result.getIndex();
}




// This is the standard modular power algorithm
// that you could find in any standard textbook,
// or on Wikipedia, but its use of the new
// modular reduction algorithm is new (in 2015).

// https://en.wikipedia.org/wiki/
//                    Exponentiation_by_squaring
// x^n = (x^2)^((n - 1)/2) if n is odd.
// x^n = (x^2)^(n/2)       if n is even.
void Mod::modPower( Integer& result,
                        Integer& exponent,
                        Integer& modulus,
                        bool usePreset,
                        IntegerMath& intMath )
{
if( result.isZero())
  return; // With Result still zero.

if( result.isEqual( modulus ))
  {
  // It is congruent to zero % ModN.
  result.setToZero();
  return;
  }

// Result is not zero at this point.
if( exponent.isZero() )
  {
  result.setFromULong( 1 );
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
  // Result stays the same.
  return;
  }

if( !usePreset )
  setupBaseArray( modulus, intMath );

Integer xForModPower;
Integer exponentCopy;
Integer tempForModPower;

xForModPower.copy( result );
exponentCopy.copy( exponent );
// Uint32 testIndex = 0;
result.setFromULong( 1 );
while( true )
  {  // If the bottom bit is 1.
  if( (exponentCopy.getD( 0 ) & 1) == 1 )
    {
    intMath.multiply( result, xForModPower );
    reduce( tempForModPower, result, intMath );
    result.copy( tempForModPower );
    }

  exponentCopy.shiftRight( 1 ); // Divide by 2.
  if( exponentCopy.isZero())
    break;

  // Square it.
  intMath.multiply( xForModPower, xForModPower );
  // IntMath.square( xForModPower );

  reduce( tempForModPower, xForModPower, intMath );
  xForModPower.copy( tempForModPower );
  }

// When this gets called it multiplies a base
// number by a uint sized digit.  So that can
// make the result one digit bigger than
// currentBase.  Then when they are added up
// you can get carry bits that can make it a
// little bigger.

Int32 howBig = result.getIndex() -
                             modulus.getIndex();
// if( howBig > 1 )
  // throw "This does happen.";

if( howBig > 2 )
  throw "This never happens. howBig.";

reduce( tempForModPower, result, intMath );
result.copy( tempForModPower );

// Notice that this Divide() is done once.
// Not a thousand or two thousand times.

makeExact( result, intMath );
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
*/