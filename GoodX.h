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
  void init( const SPrimes& sPrimes );
  inline bool getVal( const Uint32 primeAt,
                      const Uint32 where ) const
    {
    return bArrays[primeAt].getVal( where );
    }

  inline void setVal( const Uint32 primeAt,
                      const Uint32 where,
                      const bool toSet )
    {
    return bArrays[primeAt].setVal( where, toSet );
    }

  };
