// Copyright Eric Chauvin 2022.



#pragma once



#include "BasicTypes.h"
// #include "ProjConst.h"
#include "SPrimes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "MultInv.h"
#include "CrtMath.h"
#include "FileIO.h"
#include "GoodX.h"
#include "Crt2.h"
#include "QuadRes.h"


class FindFacCrt
  {
  private:
  Int32 testForCopy = 123;

  public:
  FindFacCrt( void );
  FindFacCrt( const FindFacCrt& in );
  ~FindFacCrt( void );
  bool getSmallFactor(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
                 // GoodX& goodX,
                 FileIO& mainIO );

  bool getSmallFactor1(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
                 FileIO& mainIO );

  bool getSmallFactor2(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
                 // GoodX& goodX,
                 FileIO& mainIO );

  void setGoodXQuadRes( Crt& prod,
                   GoodX& goodX,
                   const SPrimes& sPrimes,
                   const QuadRes& quadRes );

  bool getFactorsQR1( const Integer& pubKeyN,
                      Integer& find1,
                      Integer& find2,
                      IntegerMath& intMath,
                      const SPrimes& sPrimes,
                      const CrtMath& crtMath,
                      GoodX& goodX,
                      QuadRes& quadRes,
                      const MultInv& multInv,
                      FileIO& mainIO );

  bool firstTenSqr( const Integer& prod,
                    IntegerMath& intMath,
                    FileIO& mainIO );

  bool checkEasyOnes( const Integer& prod,
                      IntegerMath& intMath,
                      const SPrimes& sPrimes,
                      FileIO& mainIO );

  void showFoundFactors(
                      const Integer& pubKeyN,
                      const Integer& find1,
                      const Integer& find2,
                      const Integer& foundX,
                      IntegerMath& intMath,
                      FileIO& mainIO );

  void getBiggestX( const Integer& pubKeyN,
                    Integer& bigX,
                    IntegerMath& intMath,
                    const SPrimes& sPrimes,
                    FileIO& mainIO );

  bool hasFactors( const Crt2& testX,
                   const Integer& pubKeyN,
                  Integer& find1,
                  Integer& find2,
                  IntegerMath& intMath,
                  // const SPrimes& sPrimes,
                  const CrtMath& crtMath,
                  // GoodX& goodX,
                  // const MultInv& multInv,
                  FileIO& mainIO );

  };
