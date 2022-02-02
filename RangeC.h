// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"

// Range checking.

// I never use the C preprocessor except to use
// #include statements.


class RangeC
  {
  private:

  public:

  // Changing the name of test() to something like
  // test2() would make the compiler show where
  // all of the range checks are.
  // Same for testNothing().

  inline static void testNothing( void )
    {
    // Do nothing.
    // This should be optimized away.
    }

  inline static void test( Int64 toTest,
                           Int64 min, Int64 max,
                           const char* showIt )
    {
    if( toTest < min )
      throw showIt;

    if( toTest > max )
      throw showIt;

    }

  };
