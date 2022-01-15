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


bool FindFactorsCrt::getSmallFactor(
                         const Integer& pubKeyN,
                         Integer& find1,
                         Integer& find2,
                         IntegerMath& intMath,
                         const SPrimes& sPrimes,
                         const MultInv& multInv,
                         const CrtMath& crtMath,
                         FileIO& mainIO )
{
return getSmallFactor1( pubKeyN,
                        find1,
                        find2,
                        intMath,
                        sPrimes,
                        multInv,
                        crtMath,
                        mainIO );

}



// Very basic version that just increments
// through possible factors.
bool FindFactorsCrt::getSmallFactor1(
                         const Integer& pubKeyN,
                         Integer& find1,
                         Integer& find2,
                         IntegerMath& intMath,
                         const SPrimes& sPrimes,
                         const MultInv& multInv,
                         const CrtMath& crtMath,
                         FileIO& mainIO )
{
Integer sqrRoot;
intMath.squareRoot( pubKeyN, sqrRoot );

mainIO.appendChars( "\nSquare root: " );
Str showRoot =  intMath.toString10( sqrRoot );
mainIO.appendStr( showRoot );
mainIO.appendChars( "\n\n" );


Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

Crt2 prodCrt2;
prodCrt2.setFromCrt( prod,
                     crtMath,
                     sPrimes,
                     multInv );

const Uint32 prodLength = prodCrt2.getLength();

Crt2 prime1;
Crt2 prime2;
Crt prime1Crt;
Crt inv;
// Crt testProd;

Integer showIt;

prime1.setToOne();

// See the note in Crt2::setInvCrt() to see
// why this count goes up above a certain
// prime number.
for( Uint32 count = 0; count < 200000000; count++ )
  {
  // Count by twos.
  if( !prime1.incAt( sPrimes, 1 ))
    break;

  // It is at least 3 when it gets here.
  // This would make it congruent to zero mod 3.
  if( prime1.getD( 1 ) == 1 )
    continue;

  if( !prime1.setInvCrt( prime1Crt,
                         inv,
                         prime2,
                         prodLength,
                         prod,
                         sPrimes,
                         multInv,
                         crtMath ))
    continue;

  // Test that it is the multiplicative inverse.
  // testProd.copy( prime1Crt );
  // testProd.multiply( inv, sPrimes );
  // if( !testProd.isEqual( prod ))
    // throw "!testProd.isEqual( prod )";

  mainIO.appendChars( "\nFound it.\n" );
  mainIO.appendChars( "Prime1: " );
  prime1.toInteger( crtMath,
                    showIt,
                    intMath );

  Str showP =  intMath.toString10( showIt );
  mainIO.appendStr( showP );
  mainIO.appendChars( "\n" );

  mainIO.appendChars( "Prime2: " );
  prime2.toInteger( crtMath,
                    showIt,
                    intMath );
  Str showP2 =  intMath.toString10( showIt );
  mainIO.appendStr( showP2 );
  mainIO.appendChars( "\n\n\n" );


  prime1.toInteger( crtMath,
                    find1,
                    intMath );

  prime2.toInteger( crtMath,
                    find2,
                    intMath );

  Integer testMult;
  testMult.copy( find1 );
  intMath.multiply( testMult, find2 );
  if( !testMult.isEqual( pubKeyN ))
    throw "!testMult.isEqual( pubKeyN ))";


  return true;
  }

mainIO.appendChars( "\nWent to end.\n\n" );

return false;
}
