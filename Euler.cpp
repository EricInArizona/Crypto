// Copyright Eric Chauvin 2021.



#include "Euler.h"


bool Euler::isQuadRes( const Integer& base,
                          Uint32 prime,
                          Mod& mod,
                          IntegerMath& intMath )
{
// Euler's Criterion:
// This is related to Fermat's Little Theorem.
// See the Fermat.cpp file.

Integer exponent;
Integer result;
Integer modulus;

exponent.setFromUInt( prime );
intMath.subtractULong( exponent, 1 );
exponent.shiftRight( 1 ); // Divide by 2.

result.copy( base );
modulus.setFromUInt( prime );

mod.toPower( result, exponent, modulus, intMath );
if( result.isOne() )
  return true;
else
  return false; // Result should be Prime - 1.

}
