// Copyright Eric Chauvin 2021 - 2022.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


// RSA Cryptosystem:


// Public-Key Cryptography Standards
// (PKCS) #1: RSA Cryptography
// http://tools.ietf.org/html/rfc2437
// http://tools.ietf.org/html/rfc3447


#include "Rsa.h"
#include "../CryptoBase/Euclid.h"
#include "../CryptoBase/Division.h"
#include "FindFacSm.h"
#include "FindFacQr.h"




Rsa::Rsa( void )
{

}


Rsa::Rsa( const Rsa& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for Rsa.";
}



bool Rsa::makeKeys( FileIO& mainIO,
                    const Integer& prime1,
                    const Integer& prime2,
                    IntegerMath& intMath,
                    Mod& mod,
                    SPrimes& sPrimes )
{
pubKeyExponent.setFromLong48( PubKeyExponentL );

primeP.copy( prime1 );
primeQ.copy( prime2 );

mainIO.appendChars( "primeP:\n" );
Str showP =  intMath.toString10( primeP );
mainIO.appendStr( showP );
mainIO.appendChars( "\n" );

mainIO.appendChars( "primeQ:\n" );
Str showQ =  intMath.toString10( primeQ );
mainIO.appendStr( showQ );
mainIO.appendChars( "\n" );

if( !isGoodPair( mainIO, intMath ))
  return false;

primePMinus1.copy( primeP );

// Work on the Least Common Multiple thing for
// P - 1 and Q - 1.

intMath.subLong48( primePMinus1, 1 );
primeQMinus1.copy( primeQ );
intMath.subLong48( primeQMinus1, 1 );

phiN.copy( primePMinus1 );
intMath.multiply( phiN, primeQMinus1 );

pubKeyN.copy( primeP );
intMath.multiply( pubKeyN, primeQ );

if( !setPrivateKeys( intMath )) // mainIO ))
  throw "!setPrivateKeys().\n";
  // return false;

if( !testEncryption( mod, intMath ))
  throw "!testEncryption().\n";
  // return false;

mainIO.appendChars( "Good pair.\n\n" );


FindFacSm findFacSm;
Int64 testFac = findFacSm.findIt( pubKeyN, 1, intMath,
                                  sPrimes, mainIO );

if( testFac != 0 )
  {
  mainIO.appendChars( "FindFacSm found testFac: " );
  Str showTest( testFac );
  mainIO.appendStr( showTest );
  mainIO.appendChars( "\n" );
  }

Integer prime1Result;
Integer prime2Result;
FindFacQr findFacQr;

if( findFacQr.findIt( pubKeyN, prime1Result, prime2Result,
                      intMath, sPrimes, mainIO ))
  {
  mainIO.appendChars( "Found it.\n" );
  // Str showQr =  intMath.toString10( qrResult );
  // mainIO.appendStr( showQr );
  // mainIO.appendChars( "\n" );

  return true;
  }


mainIO.appendChars( "\nDidn't find a factor.\n" );

return true;
}



bool Rsa::isGoodPair( FileIO& mainIO,
                      IntegerMath& intMath )
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




bool Rsa::setPrivateKeys( IntegerMath& intMath )
                           // FileIO& mainIO )
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
  throw "Rsa multInverse was false. (1)\n";
  // return false;
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
  throw "Rsa multInverse was false. (2)\n";
  // return false;
  }

Integer quotient;
Integer remainder;
Integer test1;

test1.copy( privKInverseExponent );
Division::divide( test1, primePMinus1,
                  quotient, remainder, intMath );
test1.copy( remainder );
if( !test1.isEqual( privKInverseExponentDP ))
  throw "Rsa Bad privKInverseExponentDP.";

// In RFC 2437 it defines a number dQ
// which is the multiplicative
//      // inverse, mod (Q - 1) of e.  That dQ
// is named privKInverseExponentDQ here.

if( !Euclid::multInverse( pubKeyExponent,
                          primeQMinus1,
                          privKInverseExponentDQ,
                          intMath ))
  {
  throw "Rsa multInverse was false. (3)\n";
  }

test1.copy( privKInverseExponent );
Division::divide( test1, primeQMinus1,
                  quotient, remainder, intMath );
test1.copy( remainder );
if( !test1.isEqual( privKInverseExponentDQ ))
  throw "Bad privKInverseExponentDQ.\n";

return true;
}




bool Rsa::testEncryption( Mod& mod,
                          IntegerMath& intMath )
{
// This does not include the standard padding
// and all that.

// Make a random number to test
// encryption/decryption.

Integer toEncrypt;

const Int32 testIndex = primeP.getIndex() - 2;
if( testIndex < 0 )
  return true;

if( !toEncrypt.makeRandomOdd( testIndex ))
  throw "Error making toEncrypt random number.";

Integer plainTextNumber;
plainTextNumber.copy( toEncrypt );

Integer toEncryptTest;
toEncryptTest.copy( toEncrypt );

expTest.toPower( toEncryptTest,
                 pubKeyExponent,
                 pubKeyN,
                 intMath );

mod.toPower( toEncrypt, pubKeyExponent,
                        pubKeyN, intMath );

if( !toEncrypt.isEqual( toEncryptTest ))
  throw "expTest.toPower didn't work.";

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
if( !toEncrypt.makeRandomOdd( testIndex ))
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


return decryptWithQInverse( cipherTextNumber,
             toEncrypt, mod, intMath );

// return true;
}



bool Rsa::decryptWithQInverse(
             const Integer& encryptedNumber,
             Integer& decryptedNumber,
             Mod& mod,
             IntegerMath& intMath )
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

// Fix up this stuff.

// How many is optimal to avoid the division?
const Int32 howManyIsOptimal =
                          primeP.getIndex() * 3;
for( Int32 count = 0; count < howManyIsOptimal;
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

  quotient.addLong48( 1 );
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
