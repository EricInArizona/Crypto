// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "RangeC.h"


class Crt
  {
  private:
  Int32 testForCopy = 123;
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32* digitAr;

  public:
  Crt( void );
  Crt( const Crt& in );
  ~Crt( void );
  void setToZero();
  void setToOne();
  bool isZero() const;
  bool isOne() const;
  void copy( const Crt& toCopy );
  bool isEqual( const Crt& toCheck ) const;
  void add( const Crt& toAdd,
            const SPrimes& sPrimes );
  void subtract( const Crt& toSub,
                 const SPrimes& sPrimes );
  void decrement( const SPrimes& sPrimes );
  void subtractInt( const Int32 toSub,
                     const SPrimes& sPrimes );
  void multiply( const Crt& toMul,
                 const SPrimes& sPrimes );
  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes );
  void setFromInt( const Int32 setFrom,
                    const SPrimes& sPrimes );


  inline Int32 getD( const Int32 index ) const
    {
    RangeC::test( index, 0, last - 1,
            "Crt.getD() index range." );

    return digitAr[index];
    }

  inline void setD( const Int32 setTo,
                    const Int32 index )
    {
    RangeC::test( index, 0, last - 1,
            "Crt.setD() index range." );

    RangeC::test( setTo, 0, 0xFFFFFF,
            "Crt.setD() setTo range." );

    digitAr[index] = setTo;
    }

  };
