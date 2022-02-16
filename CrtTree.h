// Copyright Eric Chauvin 2022.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"
#include "GoodX.h"
#include "RangeC.h"


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



class CrtTree
  {
  private:
  Int32 testForCopy = 123;

  // This doesn't keep its own GoodX because
  // that depends on what the calling object
  // needs it for.  This uses _any_ GoodX
  // that was set up elsewhere.

  Int32* nodesAr;
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32 index = 0;

  public:
  CrtTree( void );
  CrtTree( const CrtTree& in );
  ~CrtTree( void );

  inline Int32 getD( Int32 where ) const
    {
    RangeC::test2( where, 0, last - 1,
            "CrtTree.getD where range." );

    RangeC::test2( where, 0, index,
            "CrtTree.getD index where range." );

    return nodesAr[where];
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


  inline void setFirstGoodXAt(
                   const Int32 where,
                   const GoodX& goodX )
    {
    RangeC::test2( where, 0, last - 1,
             "setFirstGoodXAt  where range." );

    index = where;
    nodesAr[index] = 0;

// Making this into a list would avoid this
// loop all together.
// Make a list object that is separate from this.
// Only a list of possible values.
// Making a list would be unknown to the calling
// function because it behaves the same on the
// outside.

    const Int32 prime = goodX.getLengthAt(
                                       where );
    for( int count = 0; count < prime; count++ )
      {
      if( goodX.getVal( where, nodesAr[where] ))
        return;

      nodesAr[where]++;

      if( nodesAr[where] >= prime )
        throw "This can't happen. setFirstGoodAt";

      }

    throw "This can't either. setFirstGoodAt";
    }

  inline bool setNextGoodXAt(
                   const Int32 where,
                   const GoodX& goodX )
    {
    RangeC::test2( where, 0, last - 1,
             "setNextGoodXAt  where range." );

    // It would have had to call setFirstGoodXAt
    // before calling this.
    RangeC::test2( where, 0, index,
         "setNextGoodXAt  where index range." );

    // It starts from where ever it left off
    // from last time.
    // nodesAr[index] = 0;

    // This is the most you could possibly
    // count through.
    const Int32 prime = goodX.getLengthAt(
                                         where );

    for( int count = 0; count < prime; count++ )
      {
      nodesAr[where]++;
      if( nodesAr[where] >= prime )
        return false;

      if( goodX.getVal( where, nodesAr[where] ))
        return true;

      }

    throw "This can't either. setNextGoodAt";
    return false;
    }

  void setFirstGoodXToDepth(
                      Int32 depth,
                      const GoodX& goodX );


  };
