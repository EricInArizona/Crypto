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




#include "../LinuxApi/BasicTypes.h"
// #include "../LinuxApi/RangeC.h"
#include "ProjConst.h"


class TwoDInt64
  {
  private:
  Int32 testForCopy = 123;
  Int64* aR;
  static const Int32 last =
                      ProjConst::digitArraySize *
                      ProjConst::digitArraySize;

  public:
  TwoDInt64( void );
  TwoDInt64( const TwoDInt64& in );
  ~TwoDInt64( void );
  inline Int64 getV( const Int32 column,
                     const Int32 row ) const
    {
    Int32 where = (row *
                   ProjConst::digitArraySize)
                   + column;

    // RangeC::test( where, 0, last - 1,
       // "TwoDInt64.getV() range for where." );

    return aR[where];
    }

  inline void setV( const Int32 column,
                    const Int32 row,
                    const Int64 val )
    {
    Int32 where = (row *
                    ProjConst::digitArraySize)
                    + column;

    // RangeC::test( where, 0, last - 1,
       // "TwoDInt64.setV() range for where." );

    aR[where] = val;
    }


  };
