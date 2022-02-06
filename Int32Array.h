// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"
#include "RangeC.h"


class Int32Array
  {
  private:
  Int32 testForCopy = 123;
  Int32 arraySize = 0;
  Int32 lastAppend = 0;
  Int32* iArray;

  void increaseAppendSize( const Int32 howMuch );

  public:
  Int32Array( void );
  Int32Array( const Int32Array& obj );
  ~Int32Array( void );
  void setSize( const Int32 howBig );
  void appendVal( const Int32 toSet );

  inline Int32 getLastAppend( void ) const
    {
    return lastAppend;
    }

  inline void clearLastAppend( void )
    {
    lastAppend = 0;
    }

  inline Int32 getVal( const Int32 where ) const
    {
    // This might not be using lastAppend.
    // It might not be using appendVal().
    // So don't test here for that range.
    RangeC::test( where, 0, arraySize - 1,
         "Int32Array.getVal arraySize range." );

    return iArray[where];
    }

  inline void setVal( const Int32 where,
                      const Int32 toSet )
    {
    RangeC::test( where, 0, arraySize - 1,
            "Int32Array.setVal where range." );

    iArray[where] = toSet;
    }

  };
