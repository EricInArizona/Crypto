// Copyright Eric Chauvin, 2021.



#pragma once

// This is 8 bytes times digitArraySize *
// digitArraySize, which is like 8 million bytes
// or 32 million bytes or something like that.




#include "BasicTypes.h"
#include "Integer.h"


class TwoDUint64
  {
  private:
  Uint64* aR;
  static const Uint32 last =
                      Integer::digitArraySize *
                      Integer::digitArraySize;

  public:
  TwoDUint64( void );
  ~TwoDUint64( void );
  inline Uint64 getV( Uint32 column, Uint32 row )
    {
    Uint32 where = (row * Integer::digitArraySize)
                   + column;
    if( where >= last )
      throw "TwoDUint64 get out of bounds.";

    return aR[where];
    }


  inline void setV( Uint32 column, Uint32 row,
                      Uint64 val )
    {
    Uint32 where = (row * Integer::digitArraySize)
                   + column;

    if( where >= last )
      throw "TwoDUint64 set out of bounds.";

    aR[where] = val;
    }


  };
