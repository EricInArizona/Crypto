// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "..\LinuxApi\BasicTypes.h"
#include "..\LinuxApi\RangeC.h"
#include "..\CryptoBase\ProjConst.h"
#include "..\CryptoBase\SPrimes.h"
#include "..\CryptoBase\Integer.h"
#include "..\CryptoBase\IntegerMath.h"


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
    RangeC::test2( index, 0, last - 1,
            "Crt.getD() index range." );

    return digitAr[index];
    }

  inline void setD( const Int32 setTo,
                    const Int32 index )
    {
    RangeC::test2( index, 0, last - 1,
            "Crt.setD() index range." );

    RangeC::test2( setTo, 0, 0xFFFFFF,
            "Crt.setD() setTo range." );

    digitAr[index] = setTo;
    }

  };
