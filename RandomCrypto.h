// Copyright Eric Chauvin 2021.


// This is supposed to be cryptographically
// random, but it probably won't be in the
// early stages of testing.


#ifndef ECRandomCrypto_H
#define ECRandomCrypto_H



#include "BasicTypes.h"
#include "Uint8Array.h"


class RandomCrypto
  {
  private:

  public:
  static void makeRandomBytes( Uint8Array& u8a,
                               Uint32 howMany );

  };


#endif
