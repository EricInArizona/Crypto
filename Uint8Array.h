// Copyright Eric Chauvin 2021.



#pragma once


#include "BasicTypes.h"
#include "Str.h"


class Uint8Array
  {
  private:
  Int32 testForCopy = 123;
  Uint32 arraySize = 0;
  Uint32 last = 0;
  Uint8* cArray;

  void increaseSize( Uint32 howMuch );

  public:
  Uint8Array( void );
  Uint8Array( const Uint8Array& obj );
  ~Uint8Array( void );
  inline Uint32 getLast( void )
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

  void appendVal( const Uint8 toSet );
  void appendArray( const Uint8* fromBuf,
                                Uint32 howMany );
  void appendStr( Str& in );
  void reverse( void );
  Uint8 valAt( Uint32 where );
  bool isAllZero( void );
  Str makeStr( void );


  };


