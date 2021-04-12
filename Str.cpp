// Copyright Eric Chauvin 2021.



#include "Str.h"
#include "StIO.h"


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

cArray = new char[arraySize];
for( Uint32 count = 0; count < arraySize; count++ )
  {
  char c = *pStr;
  cArray[count] = c;
  pStr++;
  }
}



// The copy constructor.
Str::Str( const Str& obj )
{
arraySize = obj.arraySize;
cArray = new char[arraySize];
for( Uint32 count = 0; count < arraySize; count++ )
  {
  cArray[count] = obj.cArray[count];
  }

StIO::uPrintf( "Str copy constructor called.\n" );
}



Str::~Str( void )
{
delete[] cArray;
}


char Str::charAt( Uint32 where )
{
if( where >= arraySize )
  throw "In charAt() index out of bounds.";

return cArray[where];
}


void Str::print()
{
if( arraySize == 0 )
  return;

for( Uint32 count = 0; count < arraySize; count++ )
  StIO::putC( cArray[count] );

}


void Str::printLine()
{
if( arraySize == 0 )
  {
  StIO::putC( '\n' );
  return;
  }

for( Uint32 count = 0; count < arraySize; count++ )
  StIO::putC( cArray[count] );

StIO::putC( '\n' );
}



Uint32 Str::charsLength( const char* pStr )
{
const char* sizePoint = pStr;

Uint32 howMany = 0;
for( Uint32 count = 0; count < 10000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    break;

  sizePoint++;
  howMany++;
  }

return howMany;
}
