// Copyright Eric Chauvin, 2021 -2022.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once



#include "../CppBase/BasicTypes.h"

#include "../CryptoBase/Integer.h"
#include "../CryptoBase/IntegerMath.h"
#include "../CryptoBase/Mod.h"
#include "../CryptoBase/Exponents.h"



class Rsa
  {
  private:
  Int32 testForCopy = 123;
  Integer primeP;
  Integer primeQ;
  Integer primePMinus1;
  Integer primeQMinus1;
  Integer pubKeyN;
  Integer pubKeyExponent;
  Integer privKInverseExponent;
  Integer privKInverseExponentDP;
  Integer privKInverseExponentDQ;
  Integer qInv;
  Integer phiN;
  Exponents expTest;

  public:
  // 65537 is a prime.
  // It is a commonly used exponent for RSA.
  //  It is 2^16 + 1.
  static const Int32 PubKeyExponentL = 65537;

  Rsa( void );
  Rsa( const Rsa& in );
  bool makeKeys( const Integer& prime1,
                 const Integer& prime2,
                 IntegerMath& intMath,
                 Mod& mod,
                 SPrimes& sPrimes );

  bool isGoodPair( IntegerMath& intMath );

  bool setPrivateKeys( IntegerMath& intMath );
  bool testEncryption( Mod& mod,
                           IntegerMath& intMath );
  bool decryptWithQInverse(
                 const Integer& encryptedNumber,
                 Integer& decryptedNumber,
                 Mod& mod,
                 IntegerMath& intMath );

  };
