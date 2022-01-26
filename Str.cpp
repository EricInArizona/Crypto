// Copyright Eric Chauvin 2021 - 2022.



#include "Str.h"
#include "CastE.h"



Str::Str( const char* pStr )
{
const char* sizePoint = pStr;

arraySize = 0;
for( Int32 count = 0; count < 10000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    break;

  sizePoint++;
  arraySize++;
  }

if( arraySize == 0 )
  {
  cArray = new char[1];
  return;
  }

cArray = new char[CastE::i32ToU64( arraySize )];
for( Int32 count = 0; count < arraySize;
                                       count++ )
  {
  char c = *pStr;
  cArray[count] = c;
  pStr++;
  }
}


Str::Str( char ar[], const Int32 howMany )
{
arraySize = howMany;
if( arraySize == 0 )
  {
  cArray = new char[1];
  return;
  }

cArray = new char[CastE::i32ToU64( arraySize )];
for( Int32 count = 0; count < arraySize;
                                        count++ )
  cArray[count] = ar[count];

}



Str::Str( const Str& in )
{
arraySize = in.arraySize;
if( arraySize == 0 )
  {
  cArray = new char[1];
  return;
  }

cArray = new char[CastE::i32ToU64( arraySize )];
for( Int32 count = 0; count < arraySize; count++ )
  cArray[count] = in.cArray[count];

}


Str::Str( const Str& in1, const Str& in2 )
{
arraySize = in1.arraySize + in2.arraySize;
if( arraySize == 0 )
  {
  cArray = new char[1];
  return;
  }

cArray = new char[CastE::i32ToU64( arraySize )];

Int32 last = 0;
for( Int32 count = 0; count < in1.arraySize;
                                     count++ )
  {
  cArray[last] = in1.cArray[count];
  last++;
  }

for( Int32 count = 0; count < in2.arraySize;
                                     count++ )
  {
  cArray[last] = in2.cArray[count];
  last++;
  }
}



Str::Str( Int64 n )
{
if( n == 0 )
  {
  arraySize = 1;
  cArray = new char[CastE::i32ToU64( arraySize )];
  cArray[0] = '0';
  return;
  }

char tempBuf[100] = { 1,2,3 };

Int32 last = 0;

Int64 toDivide = n;
while( toDivide != 0 )
  {
  Int64 digit = toDivide % 10;
  // Ascii values go from '0' up to '9'.
  tempBuf[last] = CastE::i32ToChar(
                  CastE::i64ToI32(('0' + digit)));
  last++;

  toDivide = toDivide / 10;
  }

arraySize = last;
cArray = new char[CastE::i32ToU64( arraySize )];

// Reverse it.
Int32 where = 0;
for( Int32 count = last - 1; count >= 0;
                                       count-- )
  {
  cArray[where] = tempBuf[count];
  where++;
  }
}



Str::~Str( void )
{
delete[] cArray;
}


void Str::copy( Str& in )
{
delete[] cArray;

arraySize = in.arraySize;

if( arraySize == 0 )
  {
  cArray = new char[1];
  return;
  }

cArray = new char[CastE::i32ToU64( arraySize )];
for( Int32 count = 0; count < arraySize; count++ )
  cArray[count] = in.cArray[count];

}



char Str::charAt( Int32 where )
{
if( where >= arraySize )
  throw "In charAt() index out of bounds.";

return cArray[where];
}



/*
void Str::print()
{
if( arraySize == 0 )
  return;

for( Uint32 count = 0; count < arraySize; count++ )
  StIO::putC( cArray[count] );

}
*/


/*
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
*/



Int32 Str::charsLength( const char* pStr )
{
const char* sizePoint = pStr;

Int32 howMany = 0;
for( Int32 count = 0; count < 10000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    break;

  sizePoint++;
  howMany++;
  }

return howMany;
}



void Str::reverse( void )
{

char* tempBuf = new char[CastE::i32ToU64(
                                 arraySize )];

// Reverse it.
Int32 where = 0;
for( Int32 count = arraySize - 1;
                              count >= 0; count-- )
  {
  tempBuf[where] = cArray[count];
  where++;
  }

for( Int32 count = 0; count < arraySize; count++ )
  cArray[count] = tempBuf[count];

delete[] tempBuf;
}
