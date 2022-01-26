// Copyright Eric Chauvin 2021 - 2022.



#pragma once



#include "BasicTypes.h"


class Str
  {
  private:
  Int32 arraySize = 0;
  char* cArray;

  public:
  Str( const char* pStr );
  Str( char ar[], const Int32 howMany );
  Str( const Str& in );
  Str( const Str& in1, const Str& in2 );
  Str( Int64 n );
  ~Str( void );
  inline Int32 getSize()
    {
    return arraySize;
    }

  void copy( Str& in );
  char charAt( Int32 where );
  // void print();
  // void printLine();
  static Int32 charsLength( const char* pStr );
  void reverse( void );

  };
