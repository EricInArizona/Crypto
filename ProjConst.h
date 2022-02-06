// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// For project-wide constants.


#include "BasicTypes.h"


class ProjConst
  {
  private:

  public:
  // digitArraySize = 100 is 2,400 bits.
  // For the prime factors used in RSA:
  // If RSA::PrimeIndex = 15 the size is 16,
  // so then N, the modulus, has a size of
  // about 32 since it is 16 + 16 long.
  // Squaring N makes it have a size of about 64.
  // So I need numbers a little bigger than
  // about 4 times the size of the RSA primes.
  // NumbSys is not exact.  It's a little
  // bigger than the modulus.

  // See Integer.h:
  static const Int32 digitArraySize = 515;

  // Test how big this can be without overflowing
  // an Integer.
  static const Int32 crtDigitArraySize =
                          digitArraySize; // * 2;

  // This is for 24 bit primes.
  static const Int32 primesArraySize =
                                     1024 * 32;


  // See Exponents.h:
  // To match this with a full size Integer it
  // should be digitArraySize * 24 bits.
  static const Int32 exponentsLast = 2000;

  // See Ellip.h:
  // The number of EPoints in an array.
  static const Int32 ellipseLast = 2000;


  };
