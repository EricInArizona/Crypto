// Copyright Eric Chauvin 2021.



// For small primes.


#ifndef ECSPrimes_H
#define ECSPrimes_H



#include "BasicTypes.h"


class SPrimes
  {
  private:
  Uint64* pArray;
  void makePrimeArray( void );

  public:
  static const Uint32 arrayLength = 1024 * 32;
  SPrimes( void );
  SPrimes( const SPrimes& obj );
  Uint64 getFirstPrimeFactor( Uint64 toTest );
  Uint64 getBiggestPrime( void );
  Uint32 getPrimeAt( Uint32 where );

  };



#endif
