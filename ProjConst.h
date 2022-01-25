// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// For project-wide constants.


#include "BasicTypes.h"


class ProjConst
  {
  private:

  public:
  // digitArraySize = 100 is 3,200 bits.
  // If RSA::PrimeIndex = 15 the size is 16,
  // so then N, the modulus, has a size of
  //about 32.  Squaring N makes it have an
  // index of about 64.  So it's about 4 times
  // the size of the primes.
  // With a PrimeIndex of 15, a
  // digitArraySize of 66 overflowed. But not
  // at 67.  16 * 4 = 64.
  // NumbSys is not exact.  It's a little
  // bigger than the modulus.

  // See Integer.h:
  static const Int32 digitArraySize = 515;

  // Test how big this can be without overflowing
  // an Integer.  It's more than twice
  // digitArraySize but less than 3 times that
  // size.
  static const Int32 crtDigitArraySize =
                          digitArraySize; // * 2;

  static const Int32 primesArraySize =
                                     1024 * 32;


  // See Exponents.h:
  // To match this with a full size Integer it
  // should be digitArraySize * 32 bits.
  static const Int32 exponentsLast = 2000;

  // See Ellip.h:
  // The number of EPoints in an array.
  static const Int32 ellipseLast = 2000;


  };
