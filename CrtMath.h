// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "IntBuf.h"
#include "SPrimes.h"
#include "Crt.h"



class CrtMath
  {
  private:
  Int32 testForCopy = 123;
  IntBuf* baseAr;
  Crt* baseArCrt;

  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  void setupBaseArray( IntegerMath& intMath,
                       SPrimes& sPrimes );

  public:
  CrtMath( void );
  CrtMath( const CrtMath& in );
  ~CrtMath( void );
  void init( IntegerMath& intMath,
                             SPrimes& sPrimes );

  void copyFromIntBuf( Integer& copyTo,
                    const Uint32 where ) const;

  inline Uint32 getCrtDigit( const Uint32 row,
                       const Uint32 col ) const
    {
    return (Uint32)baseArCrt[row].getD( col );
    }

  };
