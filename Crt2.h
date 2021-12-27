// Copyright Eric Chauvin, 2021.



#pragma once


#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"



class Crt2
  {
  private:
  Int32 testForCopy = 123;
  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  Int32* digitAr;

  public:
  Crt2( void );
  Crt2( const Crt2& in );
  ~Crt2( void );
  void setToZero();
  void setToOne();
  bool isZero();
  bool isOne();
  void copy( const Crt2& toCopy );
  bool isEqual( const Crt2& toCheck );
  bool incrementRev( SPrimes& sPrimes,
                     const Int32 top );

  inline Int32 getD( Uint32 index ) const
    {
    // Comment out after testing:
    if( index >= last )
      throw "Crt2 GetD Index is too big.";

    return digitAr[index];
    }

  inline void setD( Int32 setTo, Uint32 index )
    {
    if( index >= last )
      throw "Crt2 SetD Index is too big.";

    digitAr[index] = setTo;
    }



  };
