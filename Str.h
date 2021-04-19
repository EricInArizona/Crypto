// Copyright Eric Chauvin 2021.



#ifndef ECStr_H
#define ECStr_H



#include "BasicTypes.h"


class Str
  {
  private:
  Uint32 arraySize = 0;
  char* cArray;

  public:
  Str( const char* str );
  Str( char ar[], Uint32 howMany );
  Str( const Str& obj );
  ~Str( void );
  inline Uint32 getSize()
    {
    return arraySize;
    }

  char charAt( Uint32 where );
  void print();
  void printLine();
  static Uint32 charsLength( const char* pStr );

  };


#endif
