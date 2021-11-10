// Copyright Eric Chauvin, 2021.



#pragma once


// This is for copies of Integer.cpp objects,
// but it has a dynamically allocated array.
// As opposed to the array being on the stack.
// Also, it only keeps 32 bits for each digit,
// so it's smaller than the working array used
// in the Integer object.

#include "BasicTypes.h"
#include "ProjConst.h"


class IntBuf
  {
  private:
  Int32 testForCopy = 123;
  Uint32 index = 0;
  static const Uint32 last =
                      ProjConst::digitArraySize;
  Uint32* D;

  public:
  IntBuf( void );
  IntBuf( const IntBuf& in );
  ~IntBuf( void );
  inline Uint32 getIndex( void ) const
    {
    return index;
    }

  inline void setIndex( Uint32 setTo )
    {
    if( setTo >= last )
      throw "IntBuf setIndex() out of bounds.";

    index = setTo;
    }

  inline Uint32 getD( const Uint32 where ) const
    {
    if( where >= last )
      throw "IntBuf.getD() index out of bounds.";

    return D[where];
    }


  inline void setD( const Uint32 where,
                    const Uint64 toSet )
    {
    if( where >= last )
      throw "IntBuf.getD() index out of bounds.";

    if( toSet > 0xFFFFFFFFUL )
      throw "IntBuf.setD() setTo is too big.";

    D[where] = (Uint32)toSet;
    }

  };
