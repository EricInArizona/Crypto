// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"

// Range checking.


class RangeC
  {
  private:

  public:

  inline static void test( Int32 index,
                           Int32 min, Int32 max )
    {
    if( index < min )
      throw "Range check less than min.";

    if( index > max )
      throw "Range check more than max.";

    }

  };
