// Copyright Eric Chauvin, 2021.



#pragma once


// Elliptic Curve Crypto Systems


#include "BasicTypes.h"
#include "Integer.h"
#include "Mod.h"
#include "FileIO.h"
#include "EPoint.h"



class Ellip
  {
  private:
  Int32 testForCopy = 123;
  IntegerMath intMath;
  SPrimes sPrimes;
  Mod mod;
  EPoint* pArray;
  static const Uint32 last  =
                          ProjConst::ellipseLast;

  public:
  Ellip( void );
  Ellip( const Ellip& in );
  ~Ellip( void );
  void test( FileIO& mainIO );
  void mainTest( FileIO& mainIO );
  void makeCurvePoints(  FileIO& mainIO,
                         const Uint32 prime );

/*
  void scalarMultByAdd( const Uint32 k,
                        const Integer& modulus,
                        Mod& mod,
                        IntegerMath& intMath );

  void twoPowerByAdd( const EPoint& p,
                      const Uint32 twoPower,
                      const Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath );

  void twoPowerDoubleP( const Uint32 twoPower,
                        const EPoint p,
                        const Integer& modulus,
                        Mod& mod,
                        IntegerMath& intMath );
*/

  };
