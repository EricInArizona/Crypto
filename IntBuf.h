// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// This is for copies of Integer.cpp objects,
// but it has a dynamically allocated array.
// As opposed to the array being on the stack.

#include "BasicTypes.h"
#include "ProjConst.h"


class IntBuf
  {
  private:
  Int32 testForCopy = 123;
  Int32 index = 0;
  static const Int32 last =
                      ProjConst::digitArraySize;
  Int32* D;

  public:
  IntBuf( void );
  IntBuf( const IntBuf& in );
  ~IntBuf( void );
  inline Int32 getIndex( void ) const
    {
    return index;
    }

  inline void setIndex( Int32 setTo )
    {
    if( setTo >= last )
      throw "IntBuf setIndex() out of bounds.";

    index = setTo;
    }

  inline Int32 getD( const Int32 where ) const
    {
    if( where >= last )
      throw "IntBuf.getD() index out of bounds.";

    return D[where];
    }


  inline void setD( const Int32 where,
                    const Int32 toSet )
    {
    if( where >= last )
      throw "IntBuf.getD() index out of bounds.";

    // 24 bits.
    if( toSet > 0xFFFFFF )
      throw "IntBuf.setD() setTo is too big.";

    D[where] = toSet;
    }

  };
