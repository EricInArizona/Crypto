// Copyright Eric Chauvin, 2022.



#pragma once


#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "Uint32Array.h"



class MultInv
  {
  private:
  Int32 testForCopy = 123;
  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  Uint32Array* u32Arrays;
  Uint32 calcMultInv( const Uint32 prime,
                             const Uint32 test );

  public:
  MultInv( void );
  MultInv( const MultInv& in );
  ~MultInv( void );
  void init( const SPrimes& sPrimes );
  inline Uint32 getInv( const Uint32 primeAt,
                        const Uint32 value ) const
    {
    // Get the inverse of value.
    return u32Arrays[primeAt].getVal( value );
    }



  };
