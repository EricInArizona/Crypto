// Copyright Eric Chauvin 2021 - 2022.



#pragma once

// This is supposed to be cryptographically
// random, but this is in the early stages of
// testing.  I'm not writing a book on
// randomness just yet.



#include "BasicTypes.h"
#include "Int8Array.h"


class RandomCrypto
  {
  private:

  public:
  static void makeRandomBytes( Int8Array& i8a,
                           const Int32 howMany );

  };
