// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Crt
  {
  private:
  Int32 testForCopy = 123;
  static const Uint32 last =
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
  void subtractUint( const Uint32 toSub,
                     const SPrimes& sPrimes );
  void multiply( const Crt& toMul,
                 const SPrimes& sPrimes );
  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes );
  void setFromUInt( const Uint32 setFrom,
                    const SPrimes& sPrimes );


  inline Int32 getD( const Uint32 index ) const
    {
    // Comment out after testing:
    // if( index >= last )
      // throw "Crt GetD Index is too big.";

    return digitAr[index];
    }

  inline void setD( const Int32 setTo,
                    const Uint32 index )
    {
    // if( index >= last )
      // throw "Crt SetD Index is too big.";

    digitAr[index] = setTo;
    }



  };
