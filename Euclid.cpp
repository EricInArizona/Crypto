// Copyright Eric Chauvin 2021.


#include "Euclid.h"
#include "Division.h"


void Euclid::greatestComDiv( Integer& X,
                             Integer& Y,
                             Integer& gcd,
                             IntegerMath& intMath )
{
// This is the basic Euclidean Algorithm
// for GCD.

if( X.isZero())
  throw "Doing GCD with a param that is zero.";

if( Y.isZero())
  throw "Doing GCD with a param that is zero.";

if( X.isEqual( Y ))
  {
  gcd.copy( X );
  return;
  }

Integer gcdX;
Integer gcdY;


// Don't change the original numbers that came
// in as parameters.
if( X.paramIsGreater( Y ))
  {
  gcdX.copy( Y );
  gcdY.copy( X );
  }
else
  {
  gcdX.copy( X );
  gcdY.copy( Y );
  }

Integer quotient;
Integer remainder;

while( true )
  {
  Division::divide( gcdX, gcdY, quotient,
                    remainder, intMath );
  if( remainder.isZero())
    {
    gcd.copy( gcdY ); // It's the smaller one.
    // It can't return from this loop until
    // the remainder is zero.
    return;
    }

  gcdX.copy( gcdY );
  gcdY.copy( remainder );
  }
}




// Reciprocity.
// They have a kind of reciprical relationship.

// The extended Euclidean algorithm gives the
// multiplicative inverse.

// X is known.  X * inverse mod modulus = 1.

bool Euclid::multInverse( Integer& X,
                          Integer& modulus,
                          Integer& inverse,
                          IntegerMath& intMath )
{
// This is the extended Euclidean Algorithm.
// A*X + B*Y = GCD
// But GCD has to be 1 or there can't
// be a multiplicative inverse.

// Either A or B has to be negative here.
// A*X + B*Y = 1 If there's a multiplicative
// inverse.

// If B is negative then it is:
// A*X + -B*Y = 1
// A*X = 1 + B*Y
// A is the multiplicative inverse of X mod B.
// Or mod Y.

if( X.isZero())
  throw "MultInverse with X that is zero.\n";

if( modulus.isZero())
  throw "MultInverse with modulus that is zero.";

// if( modulus.paramIsGreaterOrEq( X ))

Integer U0;
Integer U1;
Integer U2;

Integer V0;
Integer V1;
Integer V2;

Integer T0;
Integer T1;
Integer T2;

// Don't change the original numbers that were
// passed in as references.

// U is the old part to keep.
U0.setToZero();
U1.setToOne();
U2.copy( modulus );

// V is the new part.
V0.setToOne();
V1.setToZero();
V2.copy( X );

T0.setToZero();
T1.setToZero();
T2.setToZero();

Integer quotient;
Integer remainder;

Integer temp1;
Integer temp2;

Integer testForModInverse1;
Integer testForModInverse2;

quotient.setToZero();
// while( not forever )
for( Uint32 count = 0; count < 10000; count++ )
  {
  if( U2.getIsNegative() )
    throw "The modulus was negative.\n";

  if( V2.getIsNegative() )
    throw "V2 was negative.\n";

  Division::divide( U2, V2, quotient,
                    remainder, intMath );

  // There is no multiplicative inverse if
  // GCD is more than 1.
  // Also see Pollard's P - 1 algorithm.
  if( remainder.isZero())
    return false;

  temp1.copy( U0 );
  temp2.copy( V0 );
  intMath.multiply( temp2, quotient );
  intMath.subtract( temp1, temp2 );
  T0.copy( temp1 );
  temp1.copy( U1 );
  temp2.copy( V1 );
  intMath.multiply( temp2, quotient );
  intMath.subtract( temp1, temp2 );
  T1.copy( temp1 );
  temp1.copy( U2 );
  temp2.copy( V2 );
  intMath.multiply( temp2, quotient );
  intMath.subtract( temp1, temp2 );
  T2.copy( temp1 );
  U0.copy( V0 );
  U1.copy( V1 );
  U2.copy( V2 );
  V0.copy( T0 );
  V1.copy( T1 );
  V2.copy( T2 );
  if( remainder.isOne())
    break;

  }

inverse.copy( T0 );
if( inverse.getIsNegative() )
intMath.add( inverse, modulus );
testForModInverse1.copy( inverse );
testForModInverse2.copy( X );
intMath.multiply( testForModInverse1,
                            testForModInverse2 );
Division::divide( testForModInverse1,
         modulus, quotient, remainder, intMath );

// By the definition of Multiplicative inverse:
if( !remainder.isOne())
  throw "multInverse() is wrong.\n";

return true;
}




/*
Not used:

    // This method is for: KnownNumber * ToFind = 1
    // mod Modulus
    // An example:
    // PublicKeyExponent * X = 1 mod PhiN.
    // PublicKeyExponent * X = 1 mod (P - 1)(Q - 1).
    // This means that
    // (PublicKeyExponent * X) = (Y * PhiN) + 1
    // X is less than PhiN.
    // So Y is less than PublicKExponent.
    // Y can't be zero.
    // If this equation can be solved then it can be solved modulo
    // any number.  So it has to be solvable mod PublicKExponent.
    // See: Hasse Principle.
    // This also depends on the idea that the KnownNumber is prime and
    // that there is one unique modular inverse.
*/
