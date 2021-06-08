// Copyright Eric Chauvin, 2021.



#ifndef ECRSA_H
#define ECRSA_H



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
#include "FileIO.h"



class RSA
  {
  private:
  IntegerMath intMath;
  SPrimes sPrimes;
  Integer primeP;
  // Integer primeQ;
  // Integer primePMinus1;
  // Integer primeQMinus1;
  // Integer pubKeyN;
  Integer pubKeyExponent;
  // Integer privKInverseExponent;
  // Integer privKInverseExponentDP;
  // Integer privKInverseExponentDQ;
  // Integer qInv;
  // Integer phiN;

  public:
  // 65537 is a prime.
  // It is a commonly used exponent for RSA.
  //  It is 2^16 + 1.
  static const Uint32 PubKeyExponentU = 65537;

  // The index, which is the size of the prime.
  // static const int PrimeIndex = 1; // 64-bit
  static const Uint32 PrimeIndex = 2; // 96-bit
  // static const int PrimeIndex = 3; // 128-bit
  // static const int PrimeIndex = 7; // 256-bit
  // static const int PrimeIndex = 15; // 512
  // static const int PrimeIndex = 31; // 1024
  // static const int PrimeIndex = 63; // 2048
  // static const int PrimeIndex = 127; // 4096


  // RSA( void );
  void test( FileIO& mainIO );
  void makeRSAKeys( FileIO& mainIO );

  };


#endif
