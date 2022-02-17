// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// Elliptic Curve Crypto Systems


#include "..\\LinuxApi\\BasicTypes.h"
#include "..\\LinuxApi\\FileIO.h"

#include "Integer.h"
#include "Mod.h"
#include "EPoint.h"



class Ellip
  {
  private:
  Int32 testForCopy = 123;
  IntegerMath intMath;
  SPrimes sPrimes;
  Mod mod;
  EPoint* pArray;
  static const Int32 last  =
                          ProjConst::ellipseLast;

  public:
  Ellip( void );
  Ellip( const Ellip& in );
  ~Ellip( void );
  void test( FileIO& mainIO );
  void mainTest( FileIO& mainIO );
  void makeCurvePoints(  FileIO& mainIO,
                         const Int32 prime );

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
