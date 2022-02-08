// Copyright Eric Chauvin 2021 - 2022.



#include "RsaTest.h"
#include "TimeEC.h"
#include "MakePrime.h"


RsaTest::RsaTest( void )
{

}


RsaTest::RsaTest( const RsaTest& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for RsaTest.";
}


void RsaTest::test( FileIO& mainIO )
{
mainIO.appendChars( "Starting RSA test.\n" );

TimeEC t1;

Int32 showBits = (PrimeIndex + 1) * 24;

mainIO.appendChars( "\nBits size is: " );
Str bits( showBits );
mainIO.appendStr( bits );
mainIO.appendChars( "\n" );


Integer prime1;
Integer prime2;
MakePrime makePrime;

makePrime.makeIt( prime1,
                  PrimeIndex,
                  sPrimes,
                  intMath,
                  mod );

makePrime.makeIt( prime2,
                  PrimeIndex,
                  sPrimes,
                  intMath,
                  mod );

for( Int32 count = 0; count < 10; count++ )
  {
  if( rsa.makeKeys( mainIO,
                    prime1,
                    prime2,
                    intMath,
                    mod ))
  break;
  }

TimeEC t2;

Int64 diff = t2.diffSec( t1 );

Str showTime( diff );
mainIO.appendChars( "\nSeconds: " );
mainIO.appendStr( showTime );
mainIO.appendChars( "\n\n" );
mainIO.appendChars( "Finished test.\n" );
}
