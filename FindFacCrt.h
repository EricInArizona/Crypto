// Copyright Eric Chauvin 2022.



#pragma once



#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/FileIO.h"

// #include "ProjConst.h"
#include "SPrimes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "MultInv.h"
#include "CrtMath.h"
#include "GoodX.h"
#include "Crt3.h"
#include "QuadRes.h"



class FindFacCrt
  {
  private:
  Int32 testForCopy = 123;

  public:
  FindFacCrt( void );
  FindFacCrt( const FindFacCrt& in );
  ~FindFacCrt( void );

/*
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
*/


  bool getFactorsQR( const Integer& pubKeyN,
                      Integer& find1,
                      Integer& find2,
                      IntegerMath& intMath,
                      const SPrimes& sPrimes,
                      const CrtMath& crtMath,
                      GoodX& goodX,
                      QuadRes& quadRes,
                      const MultInv& multInv,
                      FileIO& mainIO );

  bool firstTestSqrRoot( const Integer& prod,
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

  bool hasFactors( const Crt3& testX,
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
