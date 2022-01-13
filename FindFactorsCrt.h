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


class FindFactorsCrt
  {
  private:
  Int32 testForCopy = 123;

  public:
  FindFactorsCrt( void );
  FindFactorsCrt( const FindFactorsCrt& in );
  ~FindFactorsCrt( void );
  bool getSmall( const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 SPrimes& sPrimes,
                 MultInv& multInv,
                 CrtMath& crtMath,
                 FileIO& mainIO );

  };
