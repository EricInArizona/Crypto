// Copyright Eric Chauvin, 2021.



#pragma once


// This is for copies of Integer objects, but
// it has a dynamically allocated array.
// As opposed to the array being on the stack.

//   static const Uint32 digitArraySize = 515;


#include "BasicTypes.h"


class ProjConst
  {
  private:

  public:
  // digitArraySize = 100 is 3,200 bits.
  // If RSA::PrimeIndex = 15 the size is 16,
  // so then N, the modulus, has a size of
  //about 32.  Squaring N makes it have an
  // index of about 64.  So about 4 times
  // the size of the primes.
  // With a PrimeIndex of 15, a
  // digitArraySize of 66 overflowed. But not
  // at 67.  16 * 4 = 64.
  // NumbSys is not exact.  It's a little
  // bigger than the modulus.

  static const Uint32 digitArraySize = 515;


  };
