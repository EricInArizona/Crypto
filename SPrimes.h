// Copyright Eric Chauvin 2021 - 2022.



#pragma once


// For small primes.



#include "BasicTypes.h"
#include "ProjConst.h"


class SPrimes
  {
  private:
  Int32 testForCopy = 123;
  Uint32* pArray;
  void makePrimeArray( void );

  static const Uint32 last =
                   ProjConst::primesArraySize;


  public:
  SPrimes( void );
  SPrimes( const SPrimes& in );
  ~SPrimes( void );
  Uint32 getFirstPrimeFactor( Uint32 toTest );
  Uint32 getBiggestPrime( void );

  inline Uint32 getPrimeAt( Uint32 where )
    {
    // if( where >= last )
      // throw "getPrimeAt() out of bounds.";

    return pArray[where];
    }

  };
