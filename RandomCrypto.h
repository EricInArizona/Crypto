// Copyright Eric Chauvin 2021.


// This is supposed to be cryptographically
// random, but this is in the early stages of
// testing.  I'm not writing a book on
// randomness just yet.


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
