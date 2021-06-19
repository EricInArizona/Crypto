// Copyright Eric Chauvin 2021.



#include "Fermat.h"



Fermat::Fermat( void )
{
//
}


// The copy constructor.
Fermat::Fermat( const Fermat& in )
{
throw "Don't use the Fermat copy constructor.";
}


bool Fermat::makeAPrime( FileIO& mainIO,
                          Integer& result,
                          Uint32 setToIndex,
                          Uint32 howMany,
                          SPrimes& sPrimes,
                          IntegerMath& intMath )
{
mainIO.appendChars( "Top of makeAPrime().\n" );

for( Uint32 count = 0; count < 1000; count++ )
  {
  // ThreadEC::sleep( 1 );

  if( !result.makeRandomOdd( setToIndex ))
    {
    throw "Error making random number.";
    }

  // Str showS =  intMath.toString10( result );
  // mainIO.appendStr( showS );
  // mainIO.appendChars( "\n\n" );

  // Make sure that it's the size I think it is.
  if( result.getIndex() < setToIndex )
    throw "Size of random prime is wrong.";

  Uint32 testPrime = intMath.
                     isDivisibleBySmallPrime(
                                      result,
                                      sPrimes );
  if( 0 != testPrime)
    continue;

  if( !isPrime( mainIO, result, howMany, sPrimes,
                                       intMath ))
    {
    mainIO.appendChars(
                "Did not pass Fermat test.\n" );
    continue;
    }


  mainIO.appendChars(
                  "\nFound a probable prime.\n" );
  mainIO.appendChars( "Attempts: " );
  Str attem( count );
  mainIO.appendStr( attem );
  mainIO.appendChars( "\n" );
  return true; // With result.
  }

mainIO.appendChars(
            "Loops ended in makeAPrime().\n" );

return false;
}




bool Fermat::isPrime( FileIO& mainIO,
                      Integer& toTest,
                           Uint32 howMany,
                           SPrimes& sPrimes,
                           IntegerMath& intMath )
{
// Use bigger primes for Fermat test because the
// modulus can't be too small.  And also it's
// more likely to be congruent to 1 with a very
// small modulus.  In other words it's a lot more
// likely to appear to be a prime when it isn't.
// This Fermat primality test is usually
// described as using random primes to test with,
// and you could do it that way too.
// An adversary will know which primes you use
// for testing this unless they are random.
// A common way of doing this is to use a
// multiple of several primes as the base, like
// 2 * 3 * 5 * 7 = 210.


// Halfway down the array.
Uint32 startAt = SPrimes::arrayLength >> 1;

for( Uint32 count = startAt; count <
                   (howMany + startAt); count++ )
  {
  if( !isPrimeForOneValue( mainIO, toTest,
                   sPrimes.getPrimeAt( count ),
                   intMath ))
    {
    // It is definitely not a prime.
    return false;
    }
  }

// It _might_ be a prime if it passed this test.
// Increasing howMany increases the probability
// that it's a prime.

return true;
}



bool Fermat::isPrimeForOneValue( FileIO& mainIO,
                          Integer& toTest,
                          Uint64 base,
                          IntegerMath& intMath )
{
// Assume toTest is not a small number.  (Not
// the size of a small prime.)
// Normally it would be something like a 1024
// bit number or bigger, but I assume it's at
// least bigger than a 32 bit number.
// Assume this has already been checked to
// see if it's divisible by a small prime.
// A has to be coprime to P and it is here
// because toTest is not divisible by a small
// prime.
// Fermat's little theorem:
// A ^ (P - 1) is congruent to 1 mod P if P
// is a prime.
// Or: A^P - A is congruent to A mod P.
// If you multiply A by itself P times then
// divide it by P, the remainder is A.
//  (A^P / P)
// 5^3 = 125.  125 - 5 = 120.  A multiple of 5.
// 2^7 = 128.  128 - 2 = 7 * 18 (a multiple of 7.)

Integer pMinus1;
Integer A;

pMinus1.copy( toTest );
intMath.subtractULong( pMinus1, 1 );
A.setFromULong( base );

mod.toPower( A, pMinus1, toTest, true, intMath );

mainIO.appendChars(
                "Value of A:\n" );
  Str showS =  intMath.toString10( A );
  mainIO.appendStr( showS );
  mainIO.appendChars( "\n\n" );

if( A.isOne())
  return true; // It _might_ be a prime.
else
  return false; // It is definitely a
                // composite number.

}
