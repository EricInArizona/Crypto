// Copyright Eric Chauvin, 2022.



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


class FindFactorsCrt
  {
  private:
  Int32 testForCopy = 123;

  public:
  FindFactorsCrt( void );
  FindFactorsCrt( const FindFactorsCrt& in );
  ~FindFactorsCrt( void );
  bool getSmallFactor(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
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
/*
  bool getSmallFactor2(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
                 FileIO& mainIO );
*/

  void setGoodValuesMult( GoodX& goodX,
                       const SPrimes& sPrimes );

  };
