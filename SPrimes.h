// Copyright Eric Chauvin 2021 - 2022.



#pragma once


// For small primes.



#include "BasicTypes.h"
#include "ProjConst.h"


class SPrimes
  {
  private:
  Int32 testForCopy = 123;
  Int32* pArray;
  void makePrimeArray( void );

  static const Int32 last =
                   ProjConst::primesArraySize;


  public:
  SPrimes( void );
  SPrimes( const SPrimes& in );
  ~SPrimes( void );
  Int32 getFirstPrimeFactor( Int32 toTest );
  Int32 getBiggestPrime( void );

  inline Int32 getPrimeAt(
                      const Int32 where ) const
    {
    // if( where >= last )
      // throw "getPrimeAt() out of bounds.";

    return pArray[where];
    }

  };
