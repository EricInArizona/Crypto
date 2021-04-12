// Copyright Eric Chauvin 2021.



#ifndef ECCharBuf_H
#define ECCharBuf_H


// This is really a byte buffer, for just any
// bytes in general, but a byte is called a
// char in C++.  It doesn't mean a character
// like an ASCII character.


#include "BasicTypes.h"
#include "Str.h"


class CharBuf
  {
  private:
  char* cArray = 0;
  Uint32 arraySize = 0;
  Uint32 last = 0;
  void increaseSize( Uint32 howMuch );

  public:
  CharBuf( void );
  CharBuf( const CharBuf &obj );
  ~CharBuf( void );
  inline Uint32 getLast( void )
    {
    return last;
    }

  const char* getBufPoint( void )
    {
    return cArray;
    }
  void appendChars( const char* fromBuf,
                              Uint32 howMany );
  void appendStr( Str& in );

  };



#endif
