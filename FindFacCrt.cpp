// Copyright Eric Chauvin 2022.



#include "FindFacCrt.h"
#include "Division.h"
#include "QuadRes.h"



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
return getSmallFactor2( pubKeyN,
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

const Int32 prodLength = prodCrt2.getLength();

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



bool FindFacCrt::getSmallFactor2(
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

const Int32 prodLength = prodCrt2.getLength();

Crt2 prime1;
Crt2 prime2;
Crt prime1Crt;
Crt testProd;

prime1.setTo3();


// while( true )
for( Int32 count = 0; count < 200000000; count++ )
  {
  prime1.revInc1( sPrimes );

  // If it's an even number.
  if( prime1.getD( 0 ) == 0 )
    continue;

  // This would make it congruent to zero mod 3.
  if( (prime1.getD( 0 ) == 1) &&
      (prime1.getD( 1 ) == 1) )
    continue;

  // This would make it congruent to zero mod 5.
  if( (prime1.getD( 0 ) == 1) && // 1
      (prime1.getD( 1 ) == 2) && // 2 * 2
      (prime1.getD( 2 ) == 0) ) //  6
    continue;

  // This would make it congruent to zero mod 7.
  if( (prime1.getD( 0 ) == 1) && // 1
      (prime1.getD( 1 ) == 0) && // 0
      (prime1.getD( 2 ) == 1) &&//  6
      (prime1.getD( 3 ) == 0) ) //  30
    continue;

  if( !prime1.setInvCrt( prime2,
                         prodLength,
                         prod,
                         sPrimes,
                         multInv,
                         crtMath ))
    continue;

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



bool FindFacCrt::getFactorsQR1(
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

// Make sure it's not some easy factors first.
// This should not happen for RSA type numbers.
if( checkEasyOnes( pubKeyN, intMath, sPrimes,
                                     mainIO ))
  return true;

Integer bigX;
getBiggestX( pubKeyN, bigX, intMath, sPrimes,
                                      mainIO );

Crt bigXCrt;
bigXCrt.setFromInteger( bigX, intMath, sPrimes );

Crt2 bigXCrt2;
bigXCrt2.setFromCrt( bigXCrt, crtMath, sPrimes,
                                       multInv );

Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

setGoodXQuadRes( prod, goodX, sPrimes, quadRes );

Crt2 testX;

// Make it start above zero so revInc()
// doesn't start at a length of zero.
// This is why the first few x values get
// checked in firstTenSqr().
testX.setTo3();

const Int32 bigXLength = bigXCrt2.getLength();
const Int32 prodByte = pubKeyN.getD( 0 ) & 0xFF;

// testX typically goes to about the size of
// the RSA primes because both primes are
// random, which means some of the very
// highest bits will be different.  So
// subtracting one prime from the other
// will make bits in x that are about as
// high as the ones in the primes.
// And the 2 in 2x just means one bit at
// the very top.
// p1 = y - x
// p2 = y + x
// p2 - p1 = (y + x) - (y - x)
// p2 - p1 = y + x - y + x
// p2 - p1 = 2x
// So if the primes are 1024 bits then
// testX will get to somewhere around
// 1024 bits.

Int32 howMany = 0;
Int64 howManyMissed = 0;
// while( true )
for( Int64 count = 0; count < 400000000L;
                                   count++ )
  {
  // testX.revInc1( sPrimes );
  testX.revInc2( prodByte, sPrimes, goodX,
                                      crtMath );

  if( testX.digitAtTop() == 0 )
    continue;

  Int32 testXLength = testX.getLength();
  if( testXLength > bigXLength )
    {
    mainIO.appendChars(
      "\nIt never found any factors.\n" );

    return false;
    }

  // This is already done.  It doesn't catch
  // anything.
  // Int32 accumByte = testX.getAccumByte(
     //                     testXLength, crtMath );

  if( testXLength > 7 )
    {
    if( !testX.isGoodXAt( 3, goodX, crtMath,
                                  sPrimes ))
      {
      howManyMissed++;
      // testX.resetUpward( sPrimes, goodX,
      //                          crtMath );
      continue;
      }
    }

  if( testX.isGoodX( testXLength, goodX,
                     crtMath, sPrimes ) <
                    ProjConst::crtDigitArraySize )
    {
    // howManyMissed++;
    continue;
    }

  howMany++;
  if( howMany > 1 )
    throw "It missed some. howMany > 1";

  if( hasFactors( testX, pubKeyN, find1, find2,
                  intMath, crtMath,
                  mainIO ))
    {
    mainIO.appendChars( "\nhowManyMissed: " );
    Str showM( howManyMissed );
    mainIO.appendStr( showM );
    mainIO.appendChars( "\n" );

    mainIO.appendChars( "\ntestXLength: " );
    Str showT( testXLength );
    mainIO.appendStr( showT );
    mainIO.appendChars( "\n" );

    return true;
    }
  }

mainIO.appendChars( "\nWent to end.\n\n" );
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



void FindFacCrt::getBiggestX(
                         const Integer& pubKeyN,
                         Integer& bigX,
                         IntegerMath& intMath,
                         const SPrimes& sPrimes,
                         FileIO& mainIO )
{
// What's a bigger number I can use for this?
Int32 bigP = sPrimes.getBiggestPrime();

Integer p1;
Integer p2;
Integer remainder;

p1.setFromInt24( bigP );

Division::divide( pubKeyN, p1, p2,
                    remainder, intMath );

// p1 = y - x
// p2 = y + x
// p2 - p1 = (y + x) - (y - x)
// p2 - p1 = y + x - y + x
// p2 - p1 = 2x
bigX.copy( p2 );
intMath.subtract( bigX, p1 );
bigX.shiftRight( 1 ); // divide by 2.

mainIO.appendChars( "Biggest X: " );
Str showX = intMath.toString10( bigX );
mainIO.appendStr( showX );
mainIO.appendChars( "\n" );
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



void FindFacCrt::setGoodXQuadRes(
                       Crt& prod,
                       GoodX& goodX,
                       const SPrimes& sPrimes,
                       const QuadRes& quadRes )
{
goodX.setAllFalse( sPrimes );

for( Int32 row = 0; row <
            ProjConst::crtDigitArraySize; row++ )
  {
  Int32 prime = sPrimes.getPrimeAt( row );
  Int32 prodDigit = prod.getD( row );
  for( Int32 col = 0; col < prime; col++ )
    {
    Int32 x = (col * col) + prodDigit;
    x = x % prime;
    // If the x that it makes is a quad res then
    // the original col value is a goodX.
    if( quadRes.getVal( row, x ))
      goodX.setVal( row, col, true );

    }
  }
}



bool FindFacCrt::checkEasyOnes(
                         const Integer& prod,
                         // Integer& find1
                         // Integer& find2
                         IntegerMath& intMath,
                         const SPrimes& sPrimes,
                         FileIO& mainIO )
{
// RSA numbers wont be found with this.
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

// Because revInc won't start at zero.
if( firstTenSqr( prod, intMath, mainIO ))
  return true;

return false;
}


bool FindFacCrt::firstTenSqr(
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
for( Int32 count = 1; count < 11; count++ )
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
