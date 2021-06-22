// Copyright Eric Chauvin 2021.



#ifndef ECCharBuf_H
#define ECCharBuf_H


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
  Uint32 arraySize = 0;
  Uint32 last = 0;
  void increaseSize( Uint32 howMuch );

  public:
  CharBuf( void );
  CharBuf( const CharBuf &in );
  ~CharBuf( void );
  inline Uint32 getLast( void )
    {
    return last;
    }

  const char* getBufPoint( void )
    {
    return cArray;
    }
  void appendChar( const char toSet );
  void appendChars( const char* pStr );
  void appendCharBuf( const char* buf,
                      const Uint32 howMany );

  void appendStr( Str& in );
  Str getStr( void );

  };



#endif
