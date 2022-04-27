// Copyright Eric Chauvin, 2021 - 2022.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"

#include "../CryptoBase/Integer.h"
#include "../CryptoBase/IntegerMath.h"
#include "../CryptoBase/IntBuf.h"
#include "../CryptoBase/SPrimes.h"
#include "CrtBuf.h"



class CrtMath
  {
  private:
  Int32 testForCopy = 123;
  IntBuf* baseAr;
  CrtBuf* baseArCrt;

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
    RangeC::test2( row, 0, last - 1,
         "CrtMath.getCrtDigit row range." );

    RangeC::test2( col, 0, last - 1,
          "CrtMath.getCrtDigit col range." );

    return baseArCrt[row].getD( col );
    }

  inline Int32 getBaseByte( const Int32 row )
                                          const
    {
    RangeC::test2( row, 0, last - 1,
         "CrtMath.getBaseByte row range." );

    return baseAr[row].getD( 0 ) & 0xFF;
    }

  };
