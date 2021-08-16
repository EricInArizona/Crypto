// Copyright Eric Chauvin 2021.



#pragma once



#include "BasicTypes.h"


class Str
  {
  private:
  Uint32 arraySize = 0;
  char* cArray;

  public:
  Str( const char* pStr );
  Str( char ar[], Uint32 howMany );
  Str( Uint8 ar[], const Uint32 howMany );
  Str( const Str& in );
  Str( const Str& in1, const Str& in2 );
  Str( Uint64 n );
  ~Str( void );
  inline Uint32 getSize()
    {
    return arraySize;
    }

  void copy( Str& in );
  char charAt( Uint32 where );
  // void print();
  // void printLine();
  static Uint32 charsLength( const char* pStr );
  void reverse( void );

  };
