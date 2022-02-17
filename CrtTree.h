// Copyright Eric Chauvin 2022.



#pragma once



#include "..\\LinuxApi\\BasicTypes.h"
#include "..\\LinuxApi\\RangeC.h"
#include "..\\LinuxApi\\Int32Array.h"

#include "ProjConst.h"
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



class CrtTree
  {
  private:
  Int32 testForCopy = 123;

  // This doesn't keep its own GoodX because
  // that depends on what the calling object
  // needs it for.  This uses any GoodX
  // that was set up elsewhere.

  Int32Array digitsAr; // Call setSize() in the
                       // constructor.

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

    return digitsAr.getVal( where );
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

    // When this is incrementing it can set
    // lower digits to the start that are
    // lower than the index.
    if( index < where )
      index = where;

    digitsAr.setVal( where, 0 );

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
      Int32 test = digitsAr.getVal( where );
      if( goodX.getVal( where, test ))
        return; // It found the first one.

      test++;
      if( test >= prime )
        throw
        "setFirstGoodXAt never found goodX.";

      digitsAr.setVal( where, test );
      }

    throw "This can't happen. setFirstGoodAt";
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
    "setNextGoodXAt where not set first range." );

    // It starts from where ever it left off
    // from last time.

    // This is the most you could possibly
    // count through.
    const Int32 prime = goodX.getLengthAt(
                                         where );

    for( int count = 0; count < prime; count++ )
      {
      Int32 test = digitsAr.getVal( where );
      test++;
      if( test >= prime )
        return false;

      digitsAr.setVal( where, test );
      if( goodX.getVal( where, test ))
        return true;

      }

    throw "Can't get here. setNextGoodAt";
    return false;
    }

  void setFirstGoodXToDepth(
                      Int32 depth,
                      const GoodX& goodX );


  };
