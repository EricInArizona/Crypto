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

  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  BoolArray* bArrays;

  public:
  GoodX( void );
  GoodX( const GoodX& in );
  ~GoodX( void );
  void init( const SPrimes& sPrimes );
  void setAllFalse( const SPrimes& sPrimes );

  inline bool getVal( const Int32 primeAt,
                      const Int32 where ) const
    {
    // RangeC::test( primeAt, 0, last - 1,
      //      "GoodX.getVal primeAt range." );

    return bArrays[primeAt].getVal( where );
    }

  inline void setVal( const Int32 primeAt,
                      const Int32 where,
                      const bool toSet )
    {
    // RangeC::test( primeAt, 0, last - 1,
      //     "GoodX.setVal primeAt range." );

    bArrays[primeAt].setVal( where, toSet );
    }

  };
