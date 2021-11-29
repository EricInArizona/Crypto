// Copyright Eric Chauvin, 2021.


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
                 ProjConst::digitArraySize * 2;
  Int32* digitAr;

  public:
  Crt( void );
  Crt( const Crt& in );
  ~Crt( void );
  void setToZero();
  void setToOne();
  bool isZero();
  bool isOne();
  void copy( Crt& toCopy );
  bool isEqual( Crt& toCheck );
  void add( Crt& toAdd, SPrimes& sPrimes );
  void subtract( Crt& toSub, SPrimes& sPrimes );
  void decrement( SPrimes& sPrimes );
  void subtractUint( Uint32 toSub,
                     SPrimes& sPrimes );
  void multiply( Crt& toMul, SPrimes& sPrimes );
  void setFromInteger( Integer& setFrom,
                       IntegerMath& intMath,
                       SPrimes& sPrimes );
  void setFromUInt( Uint32 setFrom,
                       SPrimes& sPrimes );


  inline Int32 getD( Uint32 index )
    {
    // Comment out after testing:
    if( index >= last )
      throw "Crt GetD Index is too big.";

    return digitAr[index];
    }

  inline void setD( Int32 setTo, Uint32 index )
    {
    if( index >= last )
      throw "Crt SetD Index is too big.";

    digitAr[index] = setTo;
    }



  };
