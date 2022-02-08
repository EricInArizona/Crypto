// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "BoolArray.h"
#include "RangeC.h"



class QuadRes
  {
  private:
  Int32 testForCopy = 123;

  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  BoolArray* bArrays;

  public:
  QuadRes( void );
  QuadRes( const QuadRes& in );
  ~QuadRes( void );
  void init( const SPrimes& sPrimes );
  inline bool getVal( const Int32 primeAt,
                      const Int32 where ) const
    {
    // RangeC::test( primeAt, 0, last - 1,
      //      "QuadRes.getVal() primeAt range." );

    return bArrays[primeAt].getVal( where );
    }


  static bool bytesQR( const Int32 test );
  static bool isSmallQR( const Int32 number );
  static bool isQR17( const Int32 number );
  static bool isQR19( const Int32 number );
  static bool isQR23( const Int32 number );
  static bool isQR29( const Int32 number );

  };
