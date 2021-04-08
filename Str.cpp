// Copyright Eric Chauvin 2021.



#include "Str.h"
// #include "FileUtil.h"



Str::Str( const char* pStr )
{
const char* sizePoint = pStr;

arraySize = 0;
for( Uint32 count = 0; count < 10000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    break;

  sizePoint++;
  arraySize++;
  }

cArray = new Uint16[arraySize];
for( Uint32 count = 0; count < arraySize; count++ )
  {
  char c = *pStr;
  cArray[count] = c;
  pStr++;
  }

// FileUtil::uPrintf( "Str constructor called. " );
// FileUtil::uPrintfD( arraySize );
// FileUtil::uPrintf( "\n" );
}



Str::~Str( void )
{
delete[] cArray;
}


Uint16 Str::uCharAt( Uint32 where )
{
if( where >= arraySize )
  throw "In charAt() index out of bounds.";

return cArray[where];
}
