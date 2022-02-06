// Copyright Eric Chauvin 2022.



#include "Int32Array.h"
#include "CastE.h"


Int32Array::Int32Array( void )
{
arraySize = 1;
iArray = new Int32[CastE::i32ToU64( arraySize )];
}



Int32Array::Int32Array( const Int32Array &in )
{
arraySize = 1;
iArray = new Int32[CastE::i32ToU64( arraySize )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The Int32Array copy"
      " constructor should not be getting"
      " called.";

throw showS;
}



Int32Array::~Int32Array( void )
{
delete[] iArray;
}



void Int32Array::setSize( const Int32 howBig )
{
arraySize = howBig;

delete[] iArray;
iArray = new Int32[CastE::i32ToU64( arraySize )];
}



void Int32Array::increaseAppendSize(
                        const Int32 howMuch )
{
arraySize = arraySize + howMuch;
Int32* tempArray = new Int32[CastE::i32ToU64(
                               arraySize )];

const Int32 max = lastAppend;

for( Int32 count = 0; count < max; count++ )
  tempArray[count] = iArray[count];

delete[] iArray;
iArray = new Int32[CastE::i32ToU64( arraySize )];

for( Int32 count = 0; count < max; count++ )
  iArray[count] = tempArray[count];

delete[] tempArray;
}



void Int32Array::appendVal( const Int32 toSet )
{
if( (lastAppend + 2) <= arraySize )
  increaseAppendSize( (1024 * 2) );

iArray[lastAppend] = toSet;
lastAppend++;
}
