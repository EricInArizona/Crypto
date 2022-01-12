// Copyright Eric Chauvin 2022.



#include "FindFactorsCrt.h"
#include "Crt2.h"



FindFactorsCrt::FindFactorsCrt( void )
{
}


FindFactorsCrt::FindFactorsCrt(
                      const FindFactorsCrt& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy c for FindFactorsCrtCrt2.";
}


FindFactorsCrt::~FindFactorsCrt( void )
{
}



bool FindFactorsCrt::getSmall( Integer& pubKeyN,
                         Integer& find1,
                         Integer& find2,
                         IntegerMath& intMath,
                         SPrimes& sPrimes,
                         MultInv& multInv,
                         CrtMath& crtMath,
                         FileIO& mainIO )
{
Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

Crt2 prime1;
Crt2 prime2;
Crt prime1Crt;
Crt inv;
Crt testProd;

Integer showIt;

prime1.setToZero();

// See the note in Crt2::setInvCrt() to see
// why this count goes up above a certain
// prime number.
for( Uint32 count = 0; count < 4500; count++ )
  {
  if( !prime1.increment( sPrimes ))
    break;

  if( prime1.getD( 0 ) == 0 )
    continue;

  if( !prime1.setInvCrt( prime1Crt,
                         inv,
                         prod,
                         sPrimes,
                         multInv,
                         crtMath ))
    continue;



  mainIO.appendChars( "Prime1: " );
  prime1.toInteger( crtMath,
                    showIt,
                    intMath );




  Str showP =  intMath.toString10( showIt );
  mainIO.appendStr( showP );
  mainIO.appendChars( "\n" );

  // At this point crt and inv have no small
  // prime factors in them.

  // There is a big number Big = 2 * 3 * 5 * ...
  // all the way up to the last prime in a
  // CRT number.  The value of inv is the
  // multiplicative inverse mod Big.
  // It is unlikely to be an actual prime
  // factor of prod.  But it could be.

  Crt testProd;
  testProd.copy( prime1Crt );
  testProd.multiply( inv, sPrimes );

  if( !testProd.isEqual( prod ))
    throw "!testProd.isEquprime1Crtal( prod )";

  }

find1.setToOne();
find2.setToOne();

return true;
}
