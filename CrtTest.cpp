// Copyright Eric Chauvin 2022.



#include "../LinuxApi/Timing.h"

#include "CrtTest.h"
#include "Crt3.h"
#include "MakePrime.h"
#include "FindFacCrt.h"



CrtTest::CrtTest( void )
{
// multInv and quadRes could take a while to
// initialize with a large
// ProjConst::crtDigitArraySize.

multInv.init( sPrimes );
crtMath.init( intMath, sPrimes );
goodX.init( sPrimes );
// quadRes.init( sPrimes, mainIO );
}


CrtTest::CrtTest( const CrtTest& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for CrtTest.";
}




void CrtTest::test( FileIO& mainIO )
{
// This start time doesn't include the MultInv
// init time.
// They happen before this t1 start time.

Timing t1;

mainIO.appendChars( "Starting CRT test.\n" );

quadRes.init( sPrimes, mainIO );

Int32 primeIndex = 1;

Int32 showBits = (primeIndex + 1) * 24;

mainIO.appendChars( "\nBits size is: " );
Str bits( showBits );
mainIO.appendStr( bits );
mainIO.appendChars( "\n" );

Integer prime1;
Integer prime2;


MakePrime makePrime;

makePrime.makeIt( prime1,
                  primeIndex,
                  sPrimes,
                  intMath,
                  mod );

makePrime.makeIt( prime2,
                  primeIndex,
                  sPrimes,
                  intMath,
                  mod );

testBasics( prime1, mainIO );

// 31, 37, 41, 43, 47, 53, 59, 61, 67,
// 71, 73, 79, 83, 89, 97

// 0 + (1 * 2) = 2
// 1 + (1 * 2) = 3
// prime1.setFromInt24( 43 );
// prime2.setFromInt24( 19 );


mainIO.appendChars( "prime1:\n" );
Str showP =  intMath.toString10( prime1 );
mainIO.appendStr( showP );
mainIO.appendChars( "\n" );

mainIO.appendChars( "prime2:\n" );
Str showQ =  intMath.toString10( prime2 );
mainIO.appendStr( showQ );
mainIO.appendChars( "\n" );

Integer pubKeyN;
pubKeyN.copy( prime1 );
intMath.multiply( pubKeyN, prime2 );

mainIO.appendChars( "pubKeyN:\n" );
Str showPub =  intMath.toString10( pubKeyN );
mainIO.appendStr( showPub );
mainIO.appendChars( "\n" );


Integer find1;
Integer find2;
FindFacCrt findFacCrt;

/*
findFacCrt.getSmallFactor(
                         pubKeyN,
                         find1,
                         find2,
                         intMath,
                         sPrimes,
                         multInv,
                         crtMath,
                         mainIO );
*/


findFacCrt.getFactorsQR( pubKeyN, find1, find2,
                         intMath, sPrimes,
                         crtMath,
                         goodX,
                         quadRes,
                         multInv,
                         mainIO );

/*
mainIO.appendChars( "find1:\n" );
Str showFind1 =  intMath.toString10( find1 );
mainIO.appendStr( showFind1 );
mainIO.appendChars( "\n" );

mainIO.appendChars( "find2:\n" );
Str showFind2 =  intMath.toString10( find2 );
mainIO.appendStr( showFind2 );
mainIO.appendChars( "\n" );
*/

Timing t2;

Int64 diff = t2.diffSec( t1 );

Str showTime( diff );
mainIO.appendChars( "\nSeconds: " );
mainIO.appendStr( showTime );
mainIO.appendChars( "\n\n" );
mainIO.appendChars( "Finished test.\n" );
}




bool CrtTest::testBasics( const Integer& t1,
                          FileIO& mainIO )
{
Int32 prime = sPrimes.getPrimeAt(
           ProjConst::crtDigitArraySize - 1 );

mainIO.appendChars( "\n\nLast CRT prime is: " );
Str showIt( prime );
mainIO.appendStr( showIt );
mainIO.appendChars( "\n" );

Int32 bigPrime = sPrimes.getBiggestPrime();
mainIO.appendChars( "Biggest prime is: " );
Str showIt2( bigPrime );
mainIO.appendStr( showIt2 );
mainIO.appendChars( "\n\n" );


Crt3 test1;
test1.setFromInteger( t1, intMath, sPrimes, multInv, crtMath );


Integer result;

test1.toInteger( crtMath, result, intMath );

// If ProjConst::crtDigitArraySize is too
// small then toInteger() will come out too
// small.

if( !result.isEqual( t1 ))
  return false;


return true;
}
