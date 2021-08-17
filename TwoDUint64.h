// Copyright Eric Chauvin, 2021.



#pragma once


// This is 8 bytes times digitArraySize *
// digitArraySize.

// If it's the same row but the column is
// incremented by one, then the values are
// next to each other in ram.  And in the same
// area of the RAM cache.  So on for loops
// of columns and rows, the outside loop should
// be rows.  Then it's reading/writing to
// adjacent areas in ram in sequence.
// for( row
//   for( column




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
