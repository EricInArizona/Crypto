// Copyright Eric Chauvin 2021.


// Exponents and Discrete Logarithms


#include "Exponents.h"
#include "Division.h"


Exponents::Exponents( void )
{
}


// Copy constructor.
Exponents::Exponents( const Exponents& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't copy Exponents in copy constructor.";
}



// This is like the Mod::toPower() function
// but ....
// The doubled values go in to an array.
// For each bit.

void Exponents::toPower( Integer& result,
                   const Integer& exponent,
                   const Integer& modulus,
                   IntegerMath& intMath )
{
// result starts out as the number to be
// raised to the exponent.
// But it gets returned as the result.

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

Integer X;
Integer expCopy;
Integer temp;

// X is the number to be raised to exponent.
X.copy( result );
expCopy.copy( exponent );
// Uint32 testIndex = 0;

result.setToOne();

Int32 howBig = 0;

// For each bit.
while( true )
  {
  if( (expCopy.getD( 0 ) & 1) == 1 )
    {
    intMath.multiply( result, X );

    // temp is the result of this
    // reduce() operation.
    numbSys.reduce( temp, result, modulus,
                                      intMath );
    result.copy( temp );
    }

  expCopy.shiftRight( 1 ); // Divide by 2.
  if( expCopy.isZero())
    break;

  // intMath.multiply( X, X );
  intMath.square( X );
  numbSys.reduce( temp, X, modulus, intMath );
  X.copy( temp );
  }

// When reduce() gets called it multiplies a base
// number by a uint sized digit.  So that can
// make the result one digit bigger than the
// modulus.  Then when they are added up
// you can get carry bits that can make it a
// little bigger.

howBig = (Int32)result.getIndex() -
               (Int32)modulus.getIndex();
// if( howBig > 1 )
  // throw "This does happen.";

if( howBig > 2 )
  throw "This never happens yet. howBig.";

numbSys.reduce( temp, result, modulus, intMath );
result.copy( temp );

// Notice that this Divide() is done once.
// Not a thousand or two thousand times.
mod.makeExact( result, modulus, intMath );
}
