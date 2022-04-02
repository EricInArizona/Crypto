// Copyright Eric Chauvin, 2022.



#pragma once


#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/RangeC.h"
#include "../LinuxApi/Int32Array.h"

#include "../CryptoBase/ProjConst.h"
#include "../CryptoBase/SPrimes.h"
#include "GoodX.h"



// The first few numbers for the base:
// 1                  1
// 2                  2
// 3                  6
// 5                 30
// 7                210
// 11             2,310
// 13            30,030
// 17           510,510
// 19         9,699,690
// 23       223,092,870
// 29     6,469,693,230
// 31   200,560,490,130
// 37 7,420,738,134,810



class CrtTreeL
  {
  private:
  Int32 testForCopy = 123;
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32Array* i32Arrays;
  Int32Array indexAr;
  Int32 index = 0;

  public:
  CrtTreeL( void );
  CrtTreeL( const CrtTreeL& in );
  ~CrtTreeL( void );
  void init( const SPrimes& sPrimes, const GoodX& goodX );

  inline Int32 getD( Int32 where ) const
    {
    RangeC::test2( where, 0, last - 1,
            "CrtTree.getD where range." );

    RangeC::test2( where, 0, index,
            "CrtTree.getD index where range." );

    const Int32 digitIndexAt = indexAr.getVal( where );
    return i32Arrays[where].getVal( digitIndexAt );
    }

  inline Int32 getIndex( void  ) const
    {
    return index;
    }


  inline void setIndex( Int32 where )
    {
    RangeC::test2( where, 0, last - 1,
            "CrtTree.setIndex where range." );

    index = where;
    }


  inline void setFirstGoodXAt( const Int32 where )
    {
    RangeC::test2( where, 0, last - 1,
             "setFirstGoodXAt  where range." );

    // When this is incrementing it can set
    // lower digits to the start that are
    // lower than the index.
    if( index < where )
      index = where;

    indexAr.setVal( where, 0 );
    }


  inline bool setNextGoodXAt( const Int32 where )
    {
    RangeC::test2( where, 0, last - 1,
             "setNextGoodXAt  where range." );

    // It would have had to call setFirstGoodXAt
    // before calling this.
    RangeC::test2( where, 0, index,
             "setNextGoodXAt where not set first range." );

    // It starts from where ever it left off
    // from last time.

    // const Int32 digitIndexAt = indexAr.getVal( where );

    const Int32 max = i32Arrays[where].getLastAppend();


    Int32 test = indexAr.getVal( where );
    test++;
    if( test >= max )
      return false;

    indexAr.setVal( where, test );
    return true;
    }

  void setFirstGoodXToDepth( Int32 depth );


  };
