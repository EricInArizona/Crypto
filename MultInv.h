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

  // Uint32 prime = sPrimes.getPrimeAt(
     //      ProjConst::crtDigitArraySize - 1 );

  public:
  MultInv( void );
  MultInv( const MultInv& in );
  ~MultInv( void );

  };
