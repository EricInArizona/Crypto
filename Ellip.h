// Copyright Eric Chauvin, 2021 - 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


// Elliptic Curve Crypto Systems


#include "../CppBase/BasicTypes.h"
// #include "../CppBase/FileIO.h"

#include "../CryptoBase/Integer.h"
#include "../CryptoBase/Mod.h"
#include "../CryptoBase/EPoint.h"



class Ellip
  {
  private:
  Int32 testForCopy = 123;
  IntegerMath intMath;
  SPrimes sPrimes;
  Mod mod;
  EPoint* pArray;
  EPoint* baseArray;
  static const Int32 arraySize =
                        ProjConst::ellipseLast;
  Int32 last  = 0;
  Integer modulus;


  public:
  Ellip( void );
  Ellip( const Ellip& in );
  ~Ellip( void );
  void test( void );
  void mainTest( void );
  void makeCurvePoints( const Int32 prime );

  void testAddPoints( void );
  void testDoublePoints( void );

  bool crudeModRoot( Integer& result, Integer& right );
  void setupBases( const EPoint p );

  };
