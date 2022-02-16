// Copyright Eric Chauvin 2022.



#include "FindFacCrt.h"
#include "Division.h"
#include "QuadRes.h"
#include "QRTree.h"



FindFacCrt::FindFacCrt( void )
{
}


FindFacCrt::FindFacCrt( const FindFacCrt& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy cons for FindFacCrt.";
}


FindFacCrt::~FindFacCrt( void )
{
}


bool FindFacCrt::getSmallFactor(
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
bool FindFacCrt::getSmallFactor1(
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

const Int32 prodIndex = prodCrt2.getIndex();

Crt2 prime1;
Crt2 prime2;
Crt prime1Crt;
// Crt testProd;

prime1.setToOne();

while( true )
// for( Int32 count = 0; count < 200000000;
//                                     count++ )
  {
  // Count by twos.
  if( !prime1.incAt( sPrimes, 1 ))
    break;

  // This would make it congruent to zero mod 3.
  if( prime1.getD( 1 ) == 1 )
    continue;

  if( !prime1.setInvCrt( prime2,
                         prodIndex,
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
  Str showP1 = prime1.toStr( crtMath, intMath );
  mainIO.appendStr( showP1 );
  mainIO.appendChars( "\n" );

  mainIO.appendChars( "Prime2: " );
  Str showP2 = prime2.toStr( crtMath, intMath );
  mainIO.appendStr( showP2 );
  mainIO.appendChars( "\n\n\n" );

  prime1.toInteger( crtMath, find1, intMath );
  prime2.toInteger( crtMath, find2, intMath );

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




bool FindFacCrt::getFactorsQR(
                         const Integer& pubKeyN,
                         Integer& find1,
                         Integer& find2,
                         IntegerMath& intMath,
                         const SPrimes& sPrimes,
                         const CrtMath& crtMath,
                         GoodX& goodX,
                         QuadRes& quadRes,
                         const MultInv& multInv,
                         FileIO& mainIO )
{
find1.setToOne();
find2.setToOne();

// Test the square root function in check easy.

// Make sure it's not some easy factors first.
// This should not happen for RSA type numbers.
/*
if( checkEasyOnes( pubKeyN, intMath, sPrimes,
                                     mainIO ))
  return true;
*/

Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

QRTree qRTree;
qRTree.setStartValues( pubKeyN, goodX, quadRes,
                       // crtMath,
                       intMath,
                       sPrimes,
                       // multInv,
                       mainIO );

if( qRTree.runIt( goodX,
                 sPrimes,
                 crtMath,
                 multInv,
                 intMath,
                 mainIO ))
  {
  return true;

/*
  Crt2 testX;
  qRTree.setCrt2( testX );
  if( hasFactors( testX, pubKeyN, find1,
                  find2, intMath, crtMath,
                  mainIO ))

    return true;
*/
  }

mainIO.appendChars(
          "\nhasFactors returned falss.\n\n" );
return false;
}



bool FindFacCrt::hasFactors(
                         const Crt2& testX,
                         const Integer& pubKeyN,
                         Integer& find1,
                         Integer& find2,
                         IntegerMath& intMath,
                         // const SPrimes& sPrimes,
                         const CrtMath& crtMath,
                         // GoodX& goodX,
                         // const MultInv& multInv,
                         FileIO& mainIO )
{
Integer x;
Integer y;
Integer xSqr;

testX.toInteger( crtMath, x, intMath );
xSqr.copy( x );
intMath.square( xSqr );
xSqr.add( pubKeyN );
if( !intMath.squareRoot( xSqr, y ))
  return false;

// prod = (y + x)(y - x)
find1.copy( y );
find1.add( x );

find2.copy( y );
intMath.subtract( find2, x );

showFoundFactors( pubKeyN, find1, find2, x,
                  intMath, mainIO );

return true;
}



void FindFacCrt::showFoundFactors(
                         const Integer& pubKeyN,
                         const Integer& find1,
                         const Integer& find2,
                         const Integer& foundX,
                         IntegerMath& intMath,
                         FileIO& mainIO )
{
mainIO.appendChars( "\nFound it.\n" );

mainIO.appendChars( "X:      " );
Str showX = intMath.toString10( foundX );
mainIO.appendStr( showX );
mainIO.appendChars( "\n" );

mainIO.appendChars( "Prime1: " );
Str showP1 = intMath.toString10( find1 );
mainIO.appendStr( showP1 );
mainIO.appendChars( "\n" );

mainIO.appendChars( "Prime2: " );
Str showP2 = intMath.toString10( find2 );
mainIO.appendStr( showP2 );
mainIO.appendChars( "\n\n" );

Integer testMult;
testMult.copy( find1 );
intMath.multiply( testMult, find2 );
if( !testMult.isEqual( pubKeyN ))
  throw "!testMult.isEqual( pubKeyN ))";

}



bool FindFacCrt::checkEasyOnes(
                         const Integer& prod,
                         // Integer& find1
                         // Integer& find2
                         IntegerMath& intMath,
                         const SPrimes& sPrimes,
                         FileIO& mainIO )
{
// RSA numbers won't be found with this.
// This is to make sure I have good numbers
// to check.

// Make sure it doesn't have small prime factors.
// This tests all the primes in SPrimes.
// Up to a prime like 386,093 or so.
Int32 testPrime = intMath.
                     isDivisibleBySmallPrime(
                               prod, sPrimes );
if( 0 != testPrime)
  {
  mainIO.appendChars(
            "It had a small prime factor.\n" );

  // find1
  // find2
  return true;
  }

// Square root needs testing.
mainIO.appendChars(
            "Testing square root.\n" );


if( firstTestSqrRoot( prod, intMath, mainIO ))
  return true;

return false;
}



bool FindFacCrt::firstTestSqrRoot(
                           const Integer& prod,
                           IntegerMath& intMath,
                           FileIO& mainIO )
{
Integer sqrRoot;
if( intMath.squareRoot( prod, sqrRoot ))
  {
  mainIO.appendChars(
          "The square root was the factor.\n" );

  return true;
  }

Integer x;
for( Int32 count = 1; count < 51; count++ )
  {
  x.setFromInt24( count );
  x.square0();
  x.add( prod );
  Integer y;
  if( intMath.squareRoot( x, y ))
    {
    // prod = (y + x)(y - x)
    mainIO.appendChars(
          "It found it in the first 10 x.\n" );

    return true;
    }
  }

return false;
}
