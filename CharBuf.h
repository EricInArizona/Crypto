// Copyright Eric Chauvin 2021 - 2022.



#pragma once



// This is really a byte buffer, for just any
// bytes in general, but a byte is called a
// char in C++.  It doesn't necessarily mean a
// character like an ASCII character.


#include "BasicTypes.h"
#include "Str.h"


class CharBuf
  {
  private:
  char* cArray;
  Int32 arraySize = 0;
  Int32 last = 0;
  void increaseSize( Int32 howMuch );

  public:
  CharBuf( void );
  CharBuf( const CharBuf &in );
  ~CharBuf( void );
  inline Int32 getLast( void ) const
    {
    return last;
    }

  inline void clear( void )
    {
    last = 0;
    }

  const char* getBufPoint( void ) const
    {
    return cArray;
    }

  void appendChar( const char toSet );
  void appendChars( const char* pStr );
  void appendCharBuf( const char* buf,
                      const Int32 howMany );

  void appendStr( Str& in );
  Str getStr( void );
  inline char valAt( const Int32 where ) const
    {
    if( where >= arraySize )
      throw "In valAt() index out of bounds.";

    if( where >= last )
      throw "In valAt() past last.";

    return cArray[where];
    }

  void appendVal( const char toSet );

  };
