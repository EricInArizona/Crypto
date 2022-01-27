// Copyright Eric Chauvin 2021 - 2022.


// This needs to be merged with CharBuf.

#include "Int8Array.h"
#include "CastE.h"


Int8Array::Int8Array( void )
{
arraySize = 1024 * 64;
cArray = new Int8[CastE::i32ToU64( arraySize )];
}


Int8Array::Int8Array( const Int8Array &in )
{
// Don't copy a giant buffer.

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The Int8Array copy"
      " constructor should not be getting"
      " called.\n";

throw showS;
}



Int8Array::~Int8Array( void )
{
delete[] cArray;
}



void Int8Array::increaseSize( const Int32 howMuch )
{
arraySize = arraySize + howMuch;
Int8* tempArray = new Int8[CastE::i32ToU64(
                                     arraySize )];

const Int32 max = last;

for( Int32 count = 0; count < max; count++ )
  tempArray[count] = cArray[count];

delete[] cArray;
cArray = new Int8[CastE::i32ToU64( arraySize )];

for( Int32 count = 0; count < max; count++ )
  cArray[count] = tempArray[count];

delete[] tempArray;
}




void Int8Array::appendVal( const Int8 toSet )
{
if( (last + 2) <= arraySize )
  increaseSize( (1024 * 64) );

cArray[last] = toSet;
last++;
}



void Int8Array::appendArray(
                           const Int8* fromBuf,
                           const Int32 howMany )
{
if( ((last + 2) + howMany) <= arraySize )
  increaseSize( howMany + (1024 * 64) );

for( Int32 count = 0; count < howMany; count++ )
  {
  cArray[last] = *fromBuf;
  last++;
  fromBuf++;
  }
}



void Int8Array::appendStr( Str& in )
{
Int32 howMany = in.getSize();
if( ((last + 2) + howMany) <= arraySize )
  increaseSize( howMany + (1024 * 64) );

for( Int32 count = 0; count < howMany; count++ )
  {
  cArray[last] = in.charAt( count );
  last++;
  }
}



void Int8Array::reverse( void )
{
const Int32 max = last;

Int8* tempA = new Int8[CastE::i32ToU64( max )];
Int32 where = 0;
for( Int32 count = max - 1; count >= 0; count-- )
  {
  tempA[where] = cArray[count];
  where++;
  }

for( Int32 count = 0; count < max; count++ )
  cArray[count] = tempA[count];

delete[] tempA;
}



bool Int8Array::isAllZero( void ) const
{
const Int32 max = last;

for( Int32 count = 0; count < max; count++ )
  {
  if( cArray[count] != 0 )
    return false;

  }

return true;
}



Int8 Int8Array::valAt( const Int32 where ) const
{
if( where >= arraySize )
  throw "In valAt() index out of bounds.";

if( where >= last )
  throw "In valAt() past last.";

return cArray[where];
}



Str Int8Array::makeStr( void )
{
Str result( cArray, last );
return result;
}
