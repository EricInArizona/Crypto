// Copyright Eric Chauvin, 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/FileIO.h"

#include "../CryptoBase/Integer.h"
#include "../CryptoBase/IntegerMath.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/Mod.h"
#include "../CryptoBase/MultInv.h"
#include "CrtMath.h"
#include "../CryptoBase/GoodX.h"
#include "../CryptoBase/QuadRes.h"



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
