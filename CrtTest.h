// Copyright Eric Chauvin, 2022.



#pragma once



#include "..\LinuxApi\BasicTypes.h"
#include "..\LinuxApi\FileIO.h"

#include "..\CryptoBase\Integer.h"
#include "..\CryptoBase\IntegerMath.h"
#include "..\CryptoBase\SPrimes.h"
#include "Mod.h"
#include "..\CryptoBase\MultInv.h"
#include "CrtMath.h"
#include "..\CryptoBase\GoodX.h"
#include "..\CryptoBase\QuadRes.h"



class CrtTest
  {
  private:
  Int32 testForCopy = 123;
  IntegerMath intMath;
  SPrimes sPrimes;
  Mod mod;
  MultInv multInv;
  CrtMath crtMath;
  GoodX goodX;
  QuadRes quadRes;

  public:
  CrtTest( void );
  CrtTest( const CrtTest& in );
  void test( FileIO& mainIO );
  bool testBasics( const Integer& t1,
                   FileIO& mainIO );

  };
