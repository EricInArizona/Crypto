// Copyright Eric Chauvin 2022.



#include "BoolArray.h"
#include "CastE.h"


BoolArray::BoolArray( void )
{
arraySize = 1;
bArray = new bool[CastE::i32ToU64( arraySize )];
}


BoolArray::BoolArray( const BoolArray &in )
{
arraySize = 1;
bArray = new bool[CastE::i32ToU64( arraySize )];

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



void BoolArray::setSize( const Int32 howBig )
{
if( howBig < 0 )
  throw "BoolArray array size < 0.";

arraySize = howBig;

delete[] bArray;
bArray = new bool[CastE::i32ToU64( arraySize )];
}
