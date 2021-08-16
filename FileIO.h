// Copyright Eric Chauvin 2021.



#pragma once


#include "BasicTypes.h"
#include "CharBuf.h"


class FileIO
  {
  private:
  CharBuf cBuf;
  Uint32 testForCopy = 123;
  public:
  FileIO( void );
  FileIO( const FileIO &in );
  ~FileIO( void );
  void readAll( const char* fileName );
  void writeAll( const char* fileName );
  void appendStr( Str& in );
  void appendChars( const char* pStr );

  };
