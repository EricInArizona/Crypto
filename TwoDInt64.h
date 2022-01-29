// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// This is 8 bytes times digitArraySize *
// digitArraySize.

// If it's the same row but the column is
// incremented by one, then the values are
// next to each other in ram.  And in the same
// area of the RAM cache.  So on for-loops
// of columns and rows, the outside loop should
// be rows.  Then it's reading/writing to
// adjacent areas in ram in sequence.
// for( row
//   for( column




#include "BasicTypes.h"
#include "ProjConst.h"


class TwoDInt64
  {
  private:
  Int64* aR;
  static const Int32 last =
                      ProjConst::digitArraySize *
                      ProjConst::digitArraySize;

  public:
  TwoDInt64( void );
  ~TwoDInt64( void );
  inline Int64 getV( const Int32 column,
                     const Int32 row ) const
    {
    Int32 where = (row *
                   ProjConst::digitArraySize)
                   + column;

    // The size of this array is created with
    // the static const ProjConst::digitArraySize
    // and for-loops are done with that same
    // static const.  So it's not going to
    // go out of range.
    // For testing:
    // if( where >= last )
      // throw "TwoDUint64 get out of bounds.";

    return aR[where];
    }

  inline void setV( const Int32 column,
                    const Int32 row,
                    const Int64 val )
    {
    Int32 where = (row *
                    ProjConst::digitArraySize)
                    + column;

    // For testing:
    // if( where >= last )
      // throw "TwoDUint64 set out of bounds.";

    aR[where] = val;
    }


  };