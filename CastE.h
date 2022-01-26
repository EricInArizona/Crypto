// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"



// This is my version of doing a type cast.
// It's called Cast E for Cast Eric.
// If you did something like cast from -1
// to an unsigned type, you'd get a really
// big number.  And that would be a big problem.

class CastE
  {
  private:

  public:

  inline static AddressU64 i32ToU64( Int32 x )
    {
    if( x < 0 )
      throw "Casting from a negative x.";

    AddressU64 result = x & 0x7FFFFFFF;
    return result;
    }

  inline static AddressU64 i64ToU64( Int64 x )
    {
    if( x < 0 )
      throw "Casting from a negative x.";

    AddressU64 result = x & 0x7FFFFFFFFFFFFFFFL;
    return result;
    }

  inline static Int32 i64ToI32( Int64 x )
    {
    if( x < 0 )
      throw "Truncating from a negative x.";

    if( x > 0x7FFFFFFF )
      throw "Truncating too big of an x.";

    Int32 result = static_cast<Int32>( x );
    return result;
    }


  inline static char i32ToChar( Int32 x )
    {
    if( x < 0 )
      throw "Truncating from a negative char x.";

    if( x >= 0x7F )
      throw "Truncating too big of an char x.";

    char result = static_cast<char>( x );
    return result;
    }


  };
