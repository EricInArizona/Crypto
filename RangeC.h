// Copyright Eric Chauvin 2022.



#pragma once


// Range checking for testing.



#include "BasicTypes.h"


class RangeC
  {
  private:

  public:


  // I never use the C preprocessor except to
  // use #include statements.
  // Changing the name of test() to something like
  // test2() would make the compiler show where
  // all of the range checks are.
  // Same for testNothing().
  // So I can check the code that I am testing.
  // It would be crazy to just change a macro
  // definition without checking the code where
  // the macro is used.

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
