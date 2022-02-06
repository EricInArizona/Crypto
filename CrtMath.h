// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "IntBuf.h"
#include "SPrimes.h"
#include "Crt.h"
#include "RangeC.h"



class CrtMath
  {
  private:
  Int32 testForCopy = 123;
  IntBuf* baseAr;
  Crt* baseArCrt;

  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  void setupBaseArray( IntegerMath& intMath,
                       const SPrimes& sPrimes );

  public:
  CrtMath( void );
  CrtMath( const CrtMath& in );
  ~CrtMath( void );
  void init( IntegerMath& intMath,
             const SPrimes& sPrimes );

  void copyFromIntBuf( Integer& copyTo,
                    const Int32 where ) const;

  inline Int32 getCrtDigit( const Int32 row,
                       const Int32 col ) const
    {
    RangeC::test( row, 0, last - 1,
            "CrtMath.getCrtDigit( row range." );

    RangeC::test( col, 0, last - 1,
            "CrtMath.getCrtDigit( col range." );

    return baseArCrt[row].getD( col );
    }

  };
