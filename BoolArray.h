// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"
// #include "RangeC.h"


class BoolArray
  {
  private:
  Int32 testForCopy = 123;
  Int32 arraySize = 1;
  bool* bArray;

  public:
  BoolArray( void );
  BoolArray( const BoolArray& in );
  ~BoolArray( void );
  void setSize( const Int32 howBig );

  inline bool getVal( const Int32 where ) const
    {
    // RangeC::test( where, 0, arraySize - 1,
       //   "BoolArray.getVal() where range." );

    return bArray[where];
    }

  inline void setVal( const Int32 where,
                      const bool toSet )
    {
    // RangeC::test( where, 0, arraySize - 1,
       //   "BoolArray.setVal() where range." );

    bArray[where] = toSet;
    }


  };
