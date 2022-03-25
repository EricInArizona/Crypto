// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/FileIO.h"

#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
#include "Rsa.h"




class RsaTest
  {
  private:
  Int32 testForCopy = 123;
  IntegerMath intMath;
  SPrimes sPrimes;
  Mod mod;
  Rsa rsa;

  public:

  // The index, which makes the size of the prime.
  // static const Int32 PrimeIndex = 0; // 24-bit
  // static const Int32 PrimeIndex = 1; // 48-bit
  // static const Int32 PrimeIndex = 2; // 72-bit
  // static const Int32 PrimeIndex = 3; // 96-bit
  // static const Int32 PrimeIndex = 4; // 120-bit
  // static const Int32 PrimeIndex = 5; // 144-bit
  // static const Int32 PrimeIndex = 6; // 168-bit
  // static const Int32 PrimeIndex = 7; // 192-bit
  // static const Int32 PrimeIndex = 9; // 240
  // static const Int32 PrimeIndex = 19; // 480
  static const Int32 PrimeIndex = 29; // 720
  // static const Int32 PrimeIndex = 39; // 960
  // static const Int32 PrimeIndex = 49; // 1,200

  // Seconds 60, 88
  // static const Int32 PrimeIndex = 99; // 2.400

  // Takes too long now.
  // static const Int32 PrimeIndex = 199; // 4,800
  // static const Int32 PrimeIndex = 299; // 7.200
  // static const Int32 PrimeIndex = 399; // 9.600

  RsaTest( void );
  RsaTest( const RsaTest& in );
  void test( FileIO& mainIO );

  };
