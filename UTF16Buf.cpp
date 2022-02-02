// Copyright Eric Chauvin 2022.



#include "UTF16Buf.h"
#include "CastE.h"


UTF16Buf::UTF16Buf( void )
{
arraySize = 1024 * 2;
cArray = new UTF16[CastE::i32ToU64( arraySize )];
}


UTF16Buf::UTF16Buf( const UTF16Buf &in )
{
// Make the compiler think the in value is
// being used.
if( in.last == 123 )
  return;

// Don't copy a giant buffer.
const char* showS =
         "The UTF16Buf copy constructor"
         " should not be getting called.\n";

throw showS;
}



UTF16Buf::~UTF16Buf( void )
{
delete[] cArray;
}



void UTF16Buf::increaseSize( const Int32 howMuch )
{
arraySize = arraySize + howMuch;
UTF16* tempArray = new UTF16[CastE::i32ToU64(
                                 arraySize )];

const Int32 max = last;

for( Int32 count = 0; count < max; count++ )
  tempArray[count] = cArray[count];

delete[] cArray;
cArray = new UTF16[CastE::i32ToU64( arraySize )];

for( Int32 count = 0; count < max; count++ )
  cArray[count] = tempArray[count];

delete[] tempArray;
}



void UTF16Buf::appendVal( const UTF16 toSet )
{
if( (last + 2) <= arraySize )
  increaseSize( (1024 * 16) );

cArray[last] = toSet;
last++;
}
