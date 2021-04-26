// Copyright Eric Chauvin 2021.



#ifndef ECStIO_H
#define ECStIO_H



#include "BasicTypes.h"



class StIO
  {
  private:

  public:
  static void printFS( const char* toWrite );
  static void printFD( Int32 d );
  static void printFUD( Uint32 d );
  static void putC( Uint16 c );

  };


#endif
