// Copyright Eric Chauvin 2021.



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



RSA::RSA( void )
{

}


// The copy constructor.
RSA::RSA( const RSA& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for RSA.\n";
}


void RSA::test( FileIO& mainIO )
{
mainIO.appendChars( "Starting test.\n" );

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

  if( !Fermat::makeAPrime( mainIO, primeP,
                                   PrimeIndex,
                                   sPrimes,
                                   intMath,
                                   mod ))
    {
    mainIO.appendChars( "makeAPrime is false.\n" );
    return;
    }

  if( !Fermat::makeAPrime( mainIO, primeQ,
                                   PrimeIndex,
                                   sPrimes,
                                   intMath,
                                   mod ))
    {
    mainIO.appendChars( "makeAPrime is false.\n" );
    return;
    }

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

  if( !testEncryption( mainIO ))
    throw "!testEncryption().\n";


  mainIO.appendChars( "Good pair.\n" );
  }

mainIO.appendChars( "End of makeRSAKeys().\n" );
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




bool RSA::testEncryption( FileIO& mainIO )
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

mod.toPower( mainIO, toEncrypt,
                        pubKeyExponent,
                        pubKeyN,
                        true,
                        intMath );

Integer cipherTextNumber;
cipherTextNumber.copy( toEncrypt );

// TimeEC t1;
// TimeEC t2;

// Int64 diff = t2.diffSec( t1 );

// Str showTime( (Uint64)diff );
// mainIO.appendChars( "\nSeconds: " );
// mainIO.appendStr( showTime );
// mainIO.appendChars( "\n\n" );

mod.toPower( mainIO, toEncrypt,
                     privKInverseExponent,
                     pubKeyN, true, intMath );

if( !plainTextNumber.isEqual( toEncrypt ))
  throw "PlainTextNumber not equal.\n";
        // Because P or Q wasn't really a prime?


/*
 "Decrypt time seconds: " +
 DecryptTime.GetSecondsToNow().ToString( "N2" ));
      Worker.ReportProgress( 0, " " );
      if( Worker.CancellationPending )
        return;


      // Test the standard optimized way of
 decrypting:
      if( !ToEncrypt.MakeRandomOdd(
 PrimeIndex - 1, RandBytes ))
        {
        Worker.ReportProgress( 0,
 "Error making random number in MakeRSAKeys()." );
        return;
        }

      PlainTextNumber.Copy( ToEncrypt );
      IntMath.ModReduction.ModularPower(
 ToEncrypt, PubKeyExponent, PubKeyN, false );
      if( Worker.CancellationPending )
        return;

      CipherTextNumber.Copy( ToEncrypt );
      // QInv is the multiplicative inverse
of PrimeQ mod PrimeP.
      if( !IntMath.MultiplicativeInverse(
 PrimeQ, PrimeP, QInv, Worker ))
        throw( new Exception(
 "MultiplicativeInverse() returned false." ));

      if( QInv.IsNegative )
        throw( new Exception(
"QInv is negative." ));

      Worker.ReportProgress( 0, "QInv is: " +
 IntMath.ToString10( QInv ));
      DecryptWithQInverse( CipherTextNumber,
                           ToEncrypt,
 // Decrypt it to this.
                           PlainTextNumber,
 // Test it against this.
                           PubKeyN,
                           PrivKInverseExponentDP,
                           PrivKInverseExponentDQ,
                           PrimeP,
                           PrimeQ,
                           Worker );

      Worker.ReportProgress( 0, " " );
      Worker.ReportProgress( 0,
"Found the values:" );
      Worker.ReportProgress( 0,
 "Seconds: " +
 StartTime.GetSecondsToNow().ToString( "N0" ));

*/


return true;
}




/*
  internal bool DecryptWithQInverse(
     Integer EncryptedNumber,
     Integer DecryptedNumber,
  Integer TestDecryptedNumber,
  Integer PubKeyN,
  Integer PrivKInverseExponentDP,
  Integer PrivKInverseExponentDQ,
  Integer PrimeP,
  Integer PrimeQ,
  BackgroundWorker Worker )
    {
    Worker.ReportProgress( 0, " " );
    Worker.ReportProgress( 0,
 "Top of DecryptWithQInverse()." );
    // QInv and the dP and dQ numbers
are normally already set up before
    // you start your listening socket.
    ECTime DecryptTime = new ECTime();
    DecryptTime.SetToNow();
    // See section 5.1.2 of RFC 2437 for
 these steps:
    // http://tools.ietf.org/html/rfc2437
    //      2.2 Let m_1 = c^dP mod p.
    //      2.3 Let m_2 = c^dQ mod q.
    //      2.4 Let h = qInv ( m_1 - m_2 ) mod p.
    //      2.5 Let m = m_2 + hq.
    Worker.ReportProgress( 0, "EncryptedNumber: "
 + IntMath.ToString10( EncryptedNumber ));
    //      2.2 Let m_1 = c^dP mod p.
    TestForDecrypt.Copy( EncryptedNumber );
    IntMathForP.ModReduction.ModularPower(
 TestForDecrypt, PrivKInverseExponentDP,
 PrimeP, true );
    if( Worker.CancellationPending )
      return false;

    M1ForInverse.Copy( TestForDecrypt );
    //      2.3 Let m_2 = c^dQ mod q.
    TestForDecrypt.Copy( EncryptedNumber );
    IntMathForQ.ModReduction.ModularPower(
 TestForDecrypt, PrivKInverseExponentDQ,
 PrimeQ, true );
    if( Worker.CancellationPending )
      return false;

    M2ForInverse.Copy( TestForDecrypt );
    //      2.4 Let h = qInv ( m_1 - m_2 ) mod p.
    // How many is optimal to avoid the division?
    int HowManyIsOptimal = (PrimeP.GetIndex() * 3);
    for( int Count = 0; Count < HowManyIsOptimal;
 Count++ )
      {
      if( M1ForInverse.ParamIsGreater(
 M2ForInverse ))
        M1ForInverse.Add( PrimeP );
      else
        break;
      }

    if( M1ForInverse.ParamIsGreater(
M2ForInverse ))
      {
      M1M2SizeDiff.Copy( M2ForInverse );
      IntMath.Subtract( M1M2SizeDiff,
 M1ForInverse );
      // Unfortunately this long Divide()
 has to be done.
      IntMath.Divider.Divide( M1M2SizeDiff,
PrimeP, Quotient, Remainder );
      Quotient.AddULong( 1 );
      Worker.ReportProgress( 0, "The Quotient
 for M1M2SizeDiff is: " + IntMath.ToString10(
 Quotient ));
      IntMath.Multiply( Quotient, PrimeP );
      M1ForInverse.Add( Quotient );
      }

    M1MinusM2.Copy( M1ForInverse );
    IntMath.Subtract( M1MinusM2, M2ForInverse );
    if( M1MinusM2.IsNegative )
      throw( new Exception(
 "M1MinusM2.IsNegative is true." ));

    if( QInv.IsNegative )
      throw( new Exception(
 "QInv.IsNegative is true." ));

    HForQInv.Copy( M1MinusM2 );
    IntMath.Multiply( HForQInv, QInv );
    if( HForQInv.IsNegative )
      throw( new Exception(
 "HForQInv.IsNegative is true." ));

    if( PrimeP.ParamIsGreater( HForQInv ))
      {
      IntMath.Divider.Divide( HForQInv, PrimeP,
 Quotient, Remainder );
      HForQInv.Copy( Remainder );
      }

    //      2.5 Let m = m_2 + hq.
    DecryptedNumber.Copy( HForQInv );
    IntMath.Multiply( DecryptedNumber, PrimeQ );
    DecryptedNumber.Add( M2ForInverse );
    if( !TestDecryptedNumber.IsEqual(
DecryptedNumber ))
      throw( new Exception(
 "!TestDecryptedNumber.IsEqual(
 DecryptedNumber )." ));

    Worker.ReportProgress( 0, " " );
    Worker.ReportProgress( 0,
 "DecryptedNumber: " +
 IntMath.ToString10( DecryptedNumber ));
    Worker.ReportProgress( 0, " " );
    Worker.ReportProgress( 0,
 "TestDecryptedNumber: " +
 IntMath.ToString10( TestDecryptedNumber ));
    Worker.ReportProgress( 0, " " );
    Worker.ReportProgress( 0,
 "Decrypt with QInv time seconds: " +
 DecryptTime.GetSecondsToNow().ToString( "N2" ));
    Worker.ReportProgress( 0, " " );
    return true;
    }

*/
