// Copyright Eric Chauvin, 2021.


#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
#include "FileIO.h"
// #include "Exponents.h"



class RSA
  {
  private:
  Int32 testForCopy = 123;
  IntegerMath intMath;
  SPrimes sPrimes;
  Mod mod;
  // Exponents exp;
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
  static const Uint32 PubKeyExponentU = 65537;

  // The index, which is the size of the prime.
  // static const int PrimeIndex = 0; // 32-bit
  // static const int PrimeIndex = 1; // 64-bit
  // static const Uint32 PrimeIndex = 2; // 96-bit
  // static const int PrimeIndex = 3; // 128-bit
  // static const int PrimeIndex = 4; // 160-bit
  // static const int PrimeIndex = 5; // 192-bit
  // static const int PrimeIndex = 6; // 224-bit
  // static const int PrimeIndex = 7; // 256-bit

  // Seconds: 3 or 4 or 2
  static const int PrimeIndex = 15; // 512

  // Seconds: 27, 23, 21, 17 or 19,11, 12, 8, 7
  // static const int PrimeIndex = 31; // 1024

  // Seconds: 185 or 201   116 or 112 O2 91
  // 97 on Ofast.  92, 130, 77
  // static const int PrimeIndex = 63; // 2048

  // Seconds: 881
  // This size prime means the modulus, the
  // public key, is about 4096 times 2 bits.
  // This needs a digitArraySize of about 515.
  // static const int PrimeIndex = 127; // 4096


  RSA( void );
  RSA( const RSA& in );
  void test( FileIO& mainIO );
  void makeRSAKeys( FileIO& mainIO );
  bool isGoodPair( FileIO& mainIO );
  bool setPrivateKeys( void ); // FileIO& mainIO );
  bool testEncryption( void );
  bool decryptWithQInverse(
                 Integer& encryptedNumber,
                 Integer& decryptedNumber );

  };
