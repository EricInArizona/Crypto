// Copyright Eric Chauvin, 2022.



#pragma once


#include "BasicTypes.h"
#include "ProjConst.h"
#include "BoolArray.h"
#include "RangeC.h"
#include "SPrimes.h"



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
  void setAllFalse( void );

  inline bool getVal( const Int32 primeAt,
                      const Int32 where ) const
    {
    RangeC::test2( primeAt, 0, last - 1,
            "GoodX.getVal primeAt range." );

    // BoolArray has its own range check.
    RangeC::test2( primeAt, 0, last - 1,
            "GoodX.getVal primeAt range." );

    return bArrays[primeAt].getVal( where );
    }

  inline void setVal( const Int32 primeAt,
                      const Int32 where,
                      const bool toSet )
    {
    RangeC::test2( primeAt, 0, last - 1,
           "GoodX.setVal primeAt range." );

    bArrays[primeAt].setVal( where, toSet );
    }

  inline Int32 getLengthAt( const Int32 where )
                                          const
    {
    RangeC::test2( where, 0, last - 1,
            "getLengthAt where range." );

    return bArrays[where].getSize();
    }

  };
