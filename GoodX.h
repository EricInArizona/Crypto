// Copyright Eric Chauvin, 2022.



#pragma once


#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "BoolArray.h"





class GoodX
  {
  private:
  Int32 testForCopy = 123;

  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  BoolArray* bArrays;

  public:
  GoodX( void );
  GoodX( const GoodX& in );
  ~GoodX( void );
  void init( SPrimes& sPrimes );
  inline bool getVal( Uint32 primeAt,
                      Uint32 where )
    {
    return bArrays[primeAt].getVal( where );
    }

  inline void setVal( Uint32 primeAt,
                      Uint32 where,
                      bool toSet )
    {
    return bArrays[primeAt].setVal( where, toSet );
    }

  };
