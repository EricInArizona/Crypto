// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"


class BoolArray
  {
  private:
  Int32 testForCopy = 123;
  Uint32 arraySize = 0;
  Uint32 last = 0;
  bool* bArray;

  public:
  BoolArray( void );
  BoolArray( const BoolArray& obj );
  ~BoolArray( void );
  void setSize( const Uint32 howBig );

  inline Uint32 getLast( void ) const
    {
    return last;
    }

  inline bool getVal( const Uint32 where ) const
    {
    if( where >= arraySize )
      throw "In getVal() index out of bounds.";

    return bArray[where];
    }

  inline void setVal( const Uint32 where,
                      const bool toSet )
    {
    if( where >= arraySize )
      throw "In setVal() index out of bounds.";

    bArray[where] = toSet;
    }


  };
