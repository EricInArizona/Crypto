// Copyright Eric Chauvin 2021.



#pragma once

// This is supposed to be cryptographically
// random, but this is in the early stages of
// testing.  I'm not writing a book on
// randomness just yet.



#include "BasicTypes.h"
#include "Uint8Array.h"


class RandomCrypto
  {
  private:

  public:
  static void makeRandomBytes( Uint8Array& u8a,
                               Uint32 howMany );

  };
