// Copyright Eric Chauvin, 2021 - 2022.






#pragma once



#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/RangeC.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "Integer.h"
#include "IntegerMath.h"


class CrtBuf
  {
  private:
  Int32 testForCopy = 123;
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32* digitAr;

  public:
  CrtBuf( void );
  CrtBuf( const CrtBuf& in );
  ~CrtBuf( void );
  void setToZero();
  void setToOne();

  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes );


  inline Int32 getD( const Int32 index ) const
    {
    RangeC::test2( index, 0, last - 1,
            "CrtBuf.getD() index range." );

    return digitAr[index];
    }

  inline void setD( const Int32 setTo,
                    const Int32 index )
    {
    RangeC::test2( index, 0, last - 1,
            "CrtBuf.setD() index range." );

    RangeC::test2( setTo, 0, 0xFFFFFF,
            "Crt.setD() setTo range." );

    digitAr[index] = setTo;
    }

  };
