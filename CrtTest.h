// Copyright Eric Chauvin, 2022.



#pragma once



#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/FileIO.h"

#include "Integer.h"
#include "IntegerMath.h"
#include "SPrimes.h"
#include "Mod.h"
#include "MultInv.h"
#include "CrtMath.h"
#include "GoodX.h"
#include "QuadRes.h"



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
