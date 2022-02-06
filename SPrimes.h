// Copyright Eric Chauvin 2021 - 2022.



#pragma once


// This is only for primes up to 24 bits so that
// it matches up with one Integer digit.
// I could do an SPrimes48 for bigger primes.



#include "BasicTypes.h"
#include "ProjConst.h"
#include "RangeC.h"


class SPrimes
  {
  private:
  Int32 testForCopy = 123;
  Int32* pArray;
  void makeArray( void );

  static const Int32 last =
                   ProjConst::primesArraySize;


  public:
  SPrimes( void );
  SPrimes( const SPrimes& in );
  ~SPrimes( void );
  Int32 getFirstFactor( const Int64 toTest )
                                          const;
  inline Int32 getPrimeAt(
                      const Int32 where ) const
    {
    // RangeC::testNothing();

    RangeC::test( where, 0, last - 1,
            "SPrimes.getPrimeAt() range." );

    return pArray[where];
    }

  inline Int32 getBiggestPrime( void ) const
    {
    return pArray[last - 1];
    }

  };
