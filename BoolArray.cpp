// Copyright Eric Chauvin 2022.



#include "BoolArray.h"


BoolArray::BoolArray( void )
{
arraySize = 1;
bArray = new bool[arraySize];
}


// The copy constructor.
BoolArray::BoolArray( const BoolArray &in )
{
arraySize = 1;
bArray = new bool[arraySize];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The BoolArray copy"
      " constructor should not be getting"
      " called.";

throw showS;
}



BoolArray::~BoolArray( void )
{
delete[] bArray;
}



void BoolArray::setSize( const Uint32 howBig )
{
arraySize = howBig;

delete[] bArray;
bArray = new bool[arraySize];
}
