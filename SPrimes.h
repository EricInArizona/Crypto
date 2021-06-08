// Copyright Eric Chauvin 2021.



// For small primes.


#ifndef ECSPrimes_H
#define ECSPrimes_H



#include "BasicTypes.h"


class SPrimes
  {
  private:
  Uint32* pArray;
  void makePrimeArray( void );

  public:
  static const Uint32 arrayLength = 1024 * 32;
  SPrimes( void );
  SPrimes( const SPrimes& in );
  ~SPrimes( void );
  Uint32 getFirstPrimeFactor( Uint32 toTest );
  Uint32 getBiggestPrime( void );
  Uint32 getPrimeAt( Uint32 where );

  };



#endif
