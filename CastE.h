// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"



class CastE
  {
  private:

  public:

  inline static ArrayU64 i32ToU64( Int32 x )
    {
    if( x < 0 )
      throw "Casting negative x to U64.";

    ArrayU64 result = x & 0x7FFFFFFF;
    return result;
    }

  inline static ArrayU64 i64ToU64( Int64 x )
    {
    if( x < 0 )
      throw "Casting negative x to U64.";

    ArrayU64 result = x & 0x7FFFFFFFFFFFFFFFL;
    return result;
    }

  inline static Int32 UTF16ToI32( UTF16 x )
    {
    if( x > 0x7FFF )
      throw "Casting from too big of UTF16.";

    Int32 result = x & 0x7FFF;
    return result;
    }

  inline static Int32 U64ToI32( ArrayU64 x )
    {
    if( x > 0x7FFFFFFF )
      throw "Casting from too big of an x.";

    // Int32 result = static_cast<Int32>( x );
    Int32 result = x & 0x7FFFFFFF;
    return result;
    }


  inline static UTF16 U64ToUTF16Byte( ArrayU64 x )
    {
    // This needs to be the full 8 bits.
    // Just truncate anything over 8 bits.
    UTF16 result = x & 0xFF;
    return result;
    }

  inline static Int32 i64ToI32( Int64 x )
    {
    if( x < 0 )
      throw "Truncating from a negative x.";

    if( x > 0x7FFFFFFF )
      throw "Truncating too big of an x.";

    // Int32 result = static_cast<Int32>( x );
    Int32 result = x & 0x7FFFFFFF;
    return result;
    }


  inline static char i32ToChar( Int32 x )
    {
    if( x < 0 )
      throw "Truncating a negative: char x.";

    // For an ASCII value I don't want to
    // include the value 0x7F.
    if( x >= 0x7F )
      throw "Truncating too big of a char x.";

    // char result = static_cast<char>( x );
    char result = x & 0x7F;
    return result;
    }


  };
