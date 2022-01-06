// Copyright Eric Chauvin 2021 - 2022.



// RSA Cryptosystem:


// Public-Key Cryptography Standards
// (PKCS) #1: RSA Cryptography
// http://tools.ietf.org/html/rfc2437
// http://tools.ietf.org/html/rfc3447


#include "RSA.h"
#include "TimeEC.h"
#include "Fermat.h"
#include "Euclid.h"
#include "Division.h"
#include "Crt.h"
#include "Crt2.h"



RSA::RSA( void )
{

}


RSA::RSA( const RSA& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for RSA.\n";
}


void RSA::test( FileIO& mainIO )
{
mainIO.appendChars( "Starting RSA test.\n" );

TimeEC t1;

makeRSAKeys( mainIO );

TimeEC t2;

Int64 diff = t2.diffSec( t1 );

Str showTime( (Uint64)diff );
mainIO.appendChars( "\nSeconds: " );
mainIO.appendStr( showTime );
mainIO.appendChars( "\n\n" );
mainIO.appendChars( "Finished test.\n" );
}



void RSA::makeRSAKeys( FileIO& mainIO )
{
CrtMath crtMath;
crtMath.init( intMath, sPrimes );

pubKeyExponent.setFromULong( PubKeyExponentU );

Uint32 showBits = (PrimeIndex + 1) * 32;

mainIO.appendChars( "Making RSA keys.\n" );
mainIO.appendChars( "Bits size is: " );
Str bits( showBits );
mainIO.appendStr( bits );
mainIO.appendChars( "\n" );

for( Uint32 count = 0; count < 3; count++ )
  {
  mainIO.appendChars( "makeRSAKeys count: " );
  Str showCount( count );
  mainIO.appendStr( showCount );
  mainIO.appendChars( "\n" );

  // Let other things run.
  // ThreadEC::sleep( 1 );

  // Make two prime factors.

  Fermat::makeAPrime( primeP, PrimeIndex,
                                   sPrimes,
                                   intMath,
                                   mod );
                                   // exp,
                                   // mainIO );

  Fermat::makeAPrime( primeQ, PrimeIndex,
                                   sPrimes,
                                   intMath,
                                   mod );
                                   // exp,
                                   // mainIO );

  mainIO.appendChars( "\n" );

  mainIO.appendChars( "primeP:\n" );
  Str showP =  intMath.toString10( primeP );
  mainIO.appendStr( showP );
  mainIO.appendChars( "\n" );

  mainIO.appendChars( "primeQ:\n" );
  Str showQ =  intMath.toString10( primeQ );
  mainIO.appendStr( showQ );
  mainIO.appendChars( "\n" );

  if( !isGoodPair( mainIO ))
    continue;

  primePMinus1.copy( primeP );

  // Make sure that primePMinus1 and
  // primeQMinus1 don't have all small factors.
  // Do Pollard's algorithm to test this.

  // Work on the Least Common Multiple thing for
  // P - 1 and Q - 1.

  intMath.subtractULong( primePMinus1, 1 );
  primeQMinus1.copy( primeQ );
  intMath.subtractULong( primeQMinus1, 1 );

  phiN.copy( primePMinus1 );
  intMath.multiply( phiN, primeQMinus1 );

  pubKeyN.copy( primeP );
  intMath.multiply( pubKeyN, primeQ );

  if( !setPrivateKeys()) // mainIO ))
    throw "!setPrivateKeys().\n";
    // continue;

  if( !testEncryption())
    throw "!testEncryption().\n";

  if( !crtTest( primeP, crtMath, mainIO ))
    throw "!crtTest().";


  mainIO.appendChars( "Good pair.\n" );
  }

mainIO.appendChars( "End of makeRSAKeys().\n" );
}


bool RSA::crtTest( const Integer& t1,
                   CrtMath& crtMath,
                   FileIO& mainIO )
{
Uint32 prime = sPrimes.getPrimeAt(
           ProjConst::crtDigitArraySize - 1 );

mainIO.appendChars( "\n\nLast prime is: " );
Str showIt( prime );
mainIO.appendStr( showIt );
mainIO.appendChars( "\n\n" );


Crt test1;
test1.setFromInteger( t1, intMath, sPrimes );

// Integer accum;

Crt2 test2;

test2.setFromCrt( test1,
                  // accum,
                  crtMath,
                  sPrimes // , intMath
                  );

// if( !accum.isEqual( t1 ))
  // return false;

Integer result;

test2.toInteger( crtMath, result, intMath );

if( !result.isEqual( t1 ))
  return false;

return true;
}



bool RSA::isGoodPair( FileIO& mainIO )
{
// This is extremely unlikely since they are
// supposed to be primes, and have passed some
// primality tests.
Integer gcd;
Euclid::greatestComDiv( primeP, primeQ,
                                 gcd, intMath );
if( !gcd.isOne())
  {
  mainIO.appendChars( "Bad pair had a GCD.\n" );
  return false;
  }

Euclid::greatestComDiv( primeP, pubKeyExponent,
                              gcd, intMath );
if( !gcd.isOne())
  {
  mainIO.appendChars(
       "primeP had a GCD with pubKeyExponent.\n" );
  return false;
  }

Euclid::greatestComDiv( primeQ, pubKeyExponent,
                                 gcd, intMath );
if( !gcd.isOne())
  {
  mainIO.appendChars(
      "primeQ had a GCD with pubKeyExponent.\n" );
  return false;
  }

return true;
}




bool RSA::setPrivateKeys( void ) // FileIO& mainIO )
{
// In RFC 2437 there are commonly used
// letters/symbols to represent
// the numbers used.  So the number e
// is the public exponent.
// The number e that is used here is
// called pPubKeyExponentUint = 65537.
// In the RFC the private key d is the
// multiplicative inverse of
// e mod PhiN.  Which is mod
// (P - 1)(Q - 1).  It's called
// privKInverseExponent here.

if( !Euclid::multInverse( pubKeyExponent,
                          phiN,
                          privKInverseExponent,
                          intMath ))
  {
  throw "multInverse was false. (1)\n";
  }

// In RFC 2437 it defines a number dP
// which is the multiplicative
// inverse, mod (P - 1) of e.  That dP
// is named PrivKInverseExponentDP here.

if( !Euclid::multInverse( pubKeyExponent,
                          primePMinus1,
                          privKInverseExponentDP,
                          intMath ))
  {
  throw "multInverse was false. (2)\n";
  }

Integer quotient;
Integer remainder;

Integer test1;
test1.copy( privKInverseExponent );
Division::divide( test1, primePMinus1,
                  quotient, remainder, intMath );
test1.copy( remainder );
if( !test1.isEqual( privKInverseExponentDP ))
  throw "Bad privKInverseExponentDP.\n";

// In RFC 2437 it defines a number dQ
// which is the multiplicative
//      // inverse, mod (Q - 1) of e.  That dQ
// is named privKInverseExponentDQ here.

if( !Euclid::multInverse( pubKeyExponent,
                          primeQMinus1,
                          privKInverseExponentDQ,
                          intMath ))
  {
  throw "multInverse was false. (3)\n";
  }

test1.copy( privKInverseExponent );
Division::divide( test1, primeQMinus1,
                  quotient, remainder, intMath );
test1.copy( remainder );
if( !test1.isEqual( privKInverseExponentDQ ))
  throw "Bad privKInverseExponentDQ.\n";

return true;
}




bool RSA::testEncryption( void )
{
// Make a random number to test
// encryption/decryption.

if( PrimeIndex == 0 )
  return true;

Integer toEncrypt;

if( !toEncrypt.makeRandomOdd( (Uint32)
                         (PrimeIndex - 1 )))
  throw "Error making toEncrypt random number.";

Integer plainTextNumber;
plainTextNumber.copy( toEncrypt );

// numbSys.setupBaseArray( // mainIO,
 //                       pubKeyN,
 //                       intMath );

mod.toPower( toEncrypt, pubKeyExponent,
                        pubKeyN, intMath );

Integer cipherTextNumber;
cipherTextNumber.copy( toEncrypt );

// TimeEC t1;
// TimeEC t2;

// Int64 diff = t2.diffSec( t1 );

// Str showTime( (Uint64)diff );
// mainIO.appendChars( "\nSeconds: " );
// mainIO.appendStr( showTime );
// mainIO.appendChars( "\n\n" );

mod.toPower( toEncrypt,
                     privKInverseExponent,
                     pubKeyN, intMath );

if( !plainTextNumber.isEqual( toEncrypt ))
  throw "PlainTextNumber not equal.\n";

// Test the standard optimized way of
// decrypting:
if( !toEncrypt.makeRandomOdd( (Uint32)
                         (PrimeIndex - 1 )))
  throw "Error making toEncrypt random number.";

plainTextNumber.copy( toEncrypt );
mod.toPower( toEncrypt, pubKeyExponent,
                      pubKeyN, intMath );

cipherTextNumber.copy( toEncrypt );


// Garner's Formula:

// qInv is the multiplicative inverse
// of PrimeQ mod PrimeP.
if( !Euclid::multInverse( primeQ,
                          primeP,
                          qInv,
                          intMath ))
  throw "MultInverse() false with qInv.";


decryptWithQInverse( cipherTextNumber,
             toEncrypt );

return true;
}



bool RSA::decryptWithQInverse(
             Integer& encryptedNumber,
             Integer& decryptedNumber )
{
// See section 5.1.2 of RFC 2437 for
// these steps:
// http://tools.ietf.org/html/rfc2437

// Garner's Formula.
//      2.2 Let m_1 = c^dP mod p.
//      2.3 Let m_2 = c^dQ mod q.
//      2.4 Let h = qInv ( m_1 - m_2 ) mod p.
//      2.5 Let m = m_2 + hq.

Integer testForDecrypt;
testForDecrypt.copy( encryptedNumber );
mod.toPower( testForDecrypt,
                    privKInverseExponentDP,
                    primeP, intMath );

Integer m1ForInverse;
Integer m2ForInverse;

m1ForInverse.copy( testForDecrypt );
//      2.3 Let m_2 = c^dQ mod q.
testForDecrypt.copy( encryptedNumber );

mod.toPower( testForDecrypt,
                    privKInverseExponentDQ,
                    primeQ, intMath );

m2ForInverse.copy( testForDecrypt );
//      2.4 Let h = qInv ( m_1 - m_2 ) mod p.

// How many is optimal to avoid the division?
Uint32 howManyIsOptimal = (primeP.getIndex() * 3);
for( Uint32 count = 0; count < howManyIsOptimal;
                                      count++ )
  {
  if( m1ForInverse.paramIsGreater(
                             m2ForInverse ))
    m1ForInverse.add( primeP );
  else
    break;
  }

Integer m1M2SizeDiff;
Integer quotient;
Integer remainder;

if( m1ForInverse.paramIsGreater( m2ForInverse ))
  {
  m1M2SizeDiff.copy( m2ForInverse );
  intMath.subtract( m1M2SizeDiff, m1ForInverse );
  // Unfortunately this long Divide()
  // has to be done.
  Division::divide( m1M2SizeDiff, primeP,
                 quotient, remainder, intMath );

  quotient.addULong( 1 );
  intMath.multiply( quotient, primeP );
  m1ForInverse.add( quotient );
  }

Integer m1MinusM2;

m1MinusM2.copy( m1ForInverse );
intMath.subtract( m1MinusM2, m2ForInverse );
if( m1MinusM2.getNegative() )
  throw "m1MinusM2 is negative.";

if( qInv.getNegative() )
  throw "qInv is negative.";

Integer hForQInv;
hForQInv.copy( m1MinusM2 );
intMath.multiply( hForQInv, qInv );
if( hForQInv.getNegative() )
  throw "hForQInv is negative.";

if( primeP.paramIsGreater( hForQInv ))
  {
  Division::divide( hForQInv, primeP,
                 quotient, remainder, intMath );

  hForQInv.copy( remainder );
  }

//      2.5 Let m = m_2 + hq.
decryptedNumber.copy( hForQInv );
intMath.multiply( decryptedNumber, primeQ );
decryptedNumber.add( m2ForInverse );

if( !testForDecrypt.isEqual(
                           decryptedNumber ))
  throw "!testDecrypt.IsEqual()";

return true;
}
