// Copyright Eric Chauvin 2022.



#pragma once


// Range checking for testing.



#include "BasicTypes.h"


class RangeC
  {
  private:

  public:

  inline static void test2( Int64 toTest,
                           Int64 min, Int64 max,
                           const char* showIt )
    {
    // Comment out these lines to make an
    // empty function that does nothing.
    // This is marked as an inline function.
    // An empty inlined function ought to
    // be optimized away completely.

    if( toTest < min )
      throw showIt;

    if( toTest > max )
      throw showIt;

    }

  };
