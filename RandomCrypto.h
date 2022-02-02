// Copyright Eric Chauvin 2021 - 2022.



#pragma once

// This is supposed to be cryptographically
// random, but this is not.  It is random enough
// to test an algorithm.
// I'm not writing a long and in-depth book
// on randomness just yet.  I'll do that when
// I have a few years to set aside for that
// task.
// The more complex something is, the more
// random it looks.  Is the Universe just a
// series of meaningless random events?
// Or is it complex?
// I won't be answering that question any
// time soon.



#include "BasicTypes.h"
#include "UTF16Buf.h"


class RandomCrypto
  {
  private:

  public:
  static void makeRandomBytes( UTF16Buf& cBuf,
                           const Int32 howMany );

  };
