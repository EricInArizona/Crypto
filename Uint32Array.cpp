// Copyright Eric Chauvin 2022.



#include "Uint32Array.h"


Uint32Array::Uint32Array( void )
{
arraySize = 1;
uArray = new Uint32[arraySize];
}


// The copy constructor.
Uint32Array::Uint32Array( const Uint32Array &in )
{
arraySize = 1;
uArray = new Uint32[arraySize];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The Uint32Array copy"
      " constructor should not be getting"
      " called.";

throw showS;
}



Uint32Array::~Uint32Array( void )
{
delete[] uArray;
}



void Uint32Array::setSize( const Uint32 howBig )
{
arraySize = howBig;

delete[] uArray;
uArray = new Uint32[arraySize];
}



void Uint32Array::increaseSize(
                        const Uint32 howMuch )
{
arraySize = arraySize + howMuch;
Uint32* tempArray = new Uint32[arraySize];

const Uint32 max = last;

for( Uint32 count = 0; count < max; count++ )
  tempArray[count] = uArray[count];

delete[] uArray;
uArray = new Uint32[arraySize];

for( Uint32 count = 0; count < max; count++ )
  uArray[count] = tempArray[count];

delete[] tempArray;
}



void Uint32Array::appendVal( const Uint32 toSet )
{
if( (last + 2) <= arraySize )
  increaseSize( (1024 * 2) );

uArray[last] = toSet;
last++;
}




