// Copyright Eric Chauvin 2021.



#ifndef ECStr_H
#define ECStr_H


#include "BasicTypes.h"


class Str
  {
  private:
  Uint32 arraySize = 0;
  Uint16* cArray;

  public:
  Str( const char* str );
  ~Str( void );
  inline Uint32 getArraySize()
    {
    return arraySize;
    }
  Uint16 charAt( Uint32 where );


  };


#endif
