// Copyright Eric Chauvin 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "Str.h"


class Int8Array
  {
  private:
  Int32 testForCopy = 123;
  Int32 arraySize = 0;
  Int32 last = 0;
  Int8* cArray;

  void increaseSize( Int32 howMuch );

  public:
  Int8Array( void );
  Int8Array( const Int8Array& obj );
  ~Int8Array( void );
  inline Int32 getLast( void ) const
    {
    return last;
    }

  inline void clear( void )
    {
    last = 0;
    }

/*
  const Uint8* getBufPoint( void )
    {
    return cArray;
    }
*/

  void appendVal( const Int8 toSet );
  void appendArray( const Int8* fromBuf,
                    const Int32 howMany );
  void appendStr( Str& in );
  void reverse( void );
  Int8 valAt( const Int32 where ) const;
  bool isAllZero( void ) const;
  Str makeStr( void );

  };
