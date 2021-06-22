// Copyright Eric Chauvin 2021.



#include "Uint8Array.h"
// #include "StIO.h"


Uint8Array::Uint8Array( void )
{
arraySize = 1024 * 64;
cArray = new Uint8[arraySize];

// StIO::uPrintf(
//        "Uint8Array constructor called.\n" );
}


// The copy constructor.
Uint8Array::Uint8Array( const Uint8Array &in )
{
// Don't copy a giant buffer.

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The Uint8Array copy"
      " constructor should not be getting"
      " called.\n";

throw showS;
}



Uint8Array::~Uint8Array( void )
{
delete[] cArray;

// StIO::printFS(
   //       "Uint8Array destructor called.\n" );
}



void Uint8Array::increaseSize( Uint32 howMuch )
{
arraySize = arraySize + howMuch;
Uint8* tempArray = new Uint8[arraySize];

const Uint32 max = last;

for( Uint32 count = 0; count < max; count++ )
  tempArray[count] = cArray[count];

delete[] cArray;
cArray = new Uint8[arraySize];

for( Uint32 count = 0; count < max; count++ )
  cArray[count] = tempArray[count];

delete[] tempArray;
}




void Uint8Array::appendVal( const Uint8 toSet )
{
if( (last + 2) <= arraySize )
  increaseSize( (1024 * 64) );

cArray[last] = toSet;
last++;
}



void Uint8Array::appendArray(
                           const Uint8* fromBuf,
                           Uint32 howMany )
{
if( ((last + 2) + howMany) <= arraySize )
  increaseSize( howMany + (1024 * 64) );

for( Uint32 count = 0; count < howMany; count++ )
  {
  cArray[last] = *fromBuf;
  last++;
  fromBuf++;
  }
}



void Uint8Array::appendStr( Str& in )
{
Uint32 howMany = in.getSize();
if( ((last + 2) + howMany) <= arraySize )
  increaseSize( howMany + (1024 * 64) );

for( Uint32 count = 0; count < howMany; count++ )
  {
  cArray[last] = (Uint8)in.charAt( count );
  last++;
  }
}



void Uint8Array::reverse( void )
{
const Uint32 max = last;

Uint8* tempA = new Uint8[max];
Uint32 where = 0;
for( Int32 count = (Int32)max - 1; count >= 0;
                                      count-- )
  {
  tempA[where] = cArray[count];
  where++;
  }

for( Uint32 count = 0; count < max; count++ )
  cArray[count] = tempA[count];

delete[] tempA;
}



bool Uint8Array::isAllZero( void )
{
const Uint32 max = last;

for( Uint32 count = 0; count < max; count++ )
  {
  if( cArray[count] != 0 )
    return false;

  }

return true;
}



Uint8 Uint8Array::valAt( Uint32 where )
{
if( where >= arraySize )
  throw "In valAt() index out of bounds.";

if( where >= last )
  throw "In valAt() past last.";

return cArray[where];
}



Str Uint8Array::makeStr( void )
{
Str result( cArray, last );
return result;
}
