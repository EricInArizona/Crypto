// Copyright Eric Chauvin 2021.



#ifndef ECStIO_H
#define ECStIO_H



#include "BasicTypes.h"



class StIO
  {
  private:

  public:
  static void uPrintf( const char* toWrite );
  static void uPrintfD( Uint32 d );
  static void putC( char c );

  };


#endif
