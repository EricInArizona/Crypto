// Copyright Eric Chauvin, 2021 - 2022.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html




#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CryptoBase/ProjConst.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/Integer.h"
#include "../CryptoBase/IntegerMath.h"


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
