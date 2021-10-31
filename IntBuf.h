// Copyright Eric Chauvin, 2021.



#pragma once


// This is for copies of Integer objects, but
// it has a dynamically allocated array.
// As opposed to the array being on the stack.

//   static const Uint32 digitArraySize = 515;


#include "BasicTypes.h"


class IntBuf
  {
  private:
  Int32 testForCopy = 123;
  Uint32 index = 0;
  // static const Uint32 last =
  //                    Integer::digitArraySize;
  Uint32 last  = 0;
  Uint32* D;

  IntBuf( void );

  public:
  IntBuf( const Uint32 setSize );
  IntBuf( const IntBuf& in );
  ~IntBuf( void );
  inline Uint32 getIndex( void ) const
    {
    return index;
    }

  inline void setIndex( Uint32 setTo )
    {
    // if( setTo >= last )
      // throw "setIndex() index out of bounds.";

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
