// Copyright Eric Chauvin 2022.



#pragma once


#include "BasicTypes.h"


class Uint32Array
  {
  private:
  Int32 testForCopy = 123;
  Uint32 arraySize = 0;
  Uint32 last = 0;
  Uint32* uArray;

  void increaseSize( const Uint32 howMuch );

  public:
  Uint32Array( void );
  Uint32Array( const Uint32Array& obj );
  ~Uint32Array( void );
  void setSize( const Uint32 howBig );
  void appendVal( const Uint32 toSet );

  inline Uint32 getLast( void ) const
    {
    return last;
    }

  inline void clear( void )
    {
    last = 0;
    }

  inline Uint32 getVal( const Uint32 where ) const
    {
    if( where >= arraySize )
      throw "In getVal() index out of bounds.";

    return uArray[where];
    }

  inline void setVal( const Uint32 where, 
                      const Uint32 toSet )
    {
    if( where >= arraySize )
      throw "In setVal() index out of bounds.";

    uArray[where] = toSet;
    }


  };
