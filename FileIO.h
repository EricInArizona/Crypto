// Copyright Eric Chauvin 2021.



#ifndef ECFileIO_H
#define ECFileIO_H



#include "BasicTypes.h"
#include "CharBuf.h"


class FileIO
  {
  private:
  CharBuf cBuf;

  public:
  FileIO( void );
  FileIO( const FileIO &obj );
  ~FileIO( void );
  void readAll( const char* fileName );
  void writeAll( const char* fileName );
  void appendStr( Str& in );
  void appendChars( const char* fromBuf,
                              Uint32 howMany );

  };


#endif
