// Copyright Eric Chauvin, 2021 -2022.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
#include "FileIO.h"



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

  public:
  // 65537 is a prime.
  // It is a commonly used exponent for RSA.
  //  It is 2^16 + 1.
  static const Int32 PubKeyExponentL = 65537;

  Rsa( void );
  Rsa( const Rsa& in );
  bool makeKeys( FileIO& mainIO,
                 const Integer& prime1,
                 const Integer& prime2,
                 IntegerMath& intMath,
                 Mod& mod );
  bool isGoodPair( FileIO& mainIO,
                   IntegerMath& intMath );
  bool setPrivateKeys( IntegerMath& intMath );
  bool testEncryption( Mod& mod,
                       IntegerMath& intMath );
  bool decryptWithQInverse(
                 const Integer& encryptedNumber,
                 Integer& decryptedNumber,
                 Mod& mod,
                 IntegerMath& intMath );

  };
