// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// For project-wide constants.


#include "BasicTypes.h"


class ProjConst
  {
  private:

  public:
  // digitArraySize = 100 is 2,400 bits.
  // If the prime is x bits long then the
  // modulus is 2 times X bits long and the
  // modulus squared is 4 times X bits long.
  // A prime of 2K bits requires 8K sized
  // numbers. 
  // NumbSys is not exact.  It's a little
  // bigger than the modulus.

  // See Integer.h:
  // 5 times 2,400 bits.
  static const Int32 digitArraySize = 500;

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
