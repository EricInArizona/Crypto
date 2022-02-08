// Copyright Eric Chauvin 2022.



#include "GoodX.h"


GoodX::GoodX( void )
{
bArrays = new BoolArray[last];
}


GoodX::GoodX( const GoodX& in )
{
bArrays = new BoolArray[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for GoodX.";
}


GoodX::~GoodX( void )
{
delete[] bArrays;
}



void GoodX::init( const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  bArrays[count].setSize( prime );

  for( Int32 countF = 0; countF < prime;
                                    countF++ )
    {
    bArrays[count].setVal( countF, false );
    }
  }
}



void GoodX::setAllFalse( const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );

  for( Int32 countF = 0; countF < prime;
                                    countF++ )
    {
    bArrays[count].setVal( countF, false );
    }
  }
}
