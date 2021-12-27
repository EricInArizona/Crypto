// Copyright Eric Chauvin 2021.



#include "Crt2.h"



Crt2::Crt2( void )
{
digitAr = new Int32[last];
setToZero();
}


Crt2::Crt2( const Crt2& in )
{
digitAr = new Int32[last];

// setToZero();

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for Crt2.\n";
}


Crt2::~Crt2( void )
{
delete[] digitAr;
}



void Crt2::setToZero()
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = 0;

}



void Crt2::setToOne()
{
for( Uint32 count = 1; count < last; count++ )
  digitAr[count] = 0;

digitAr[0] = 1;
}




bool Crt2::isZero()
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 0 )
    return false;

  }

return true;
}



bool Crt2::isOne()
{
if( digitAr[0] != 1 )
  return false;

for( Uint32 count = 1; count < last; count++ )
  {
  if( digitAr[count] != 0 )
    return false;

  }

return true;
}



void Crt2::copy( const Crt2& toCopy )
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt2::isEqual( const Crt2& toCheck )
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}



bool Crt2::incrementRev( SPrimes& sPrimes,
                         const Int32 top )
{
// Change the digits from the top so that
// lower accumulate values can stay the same.

for( Int32 count = top; count >= 0; count-- )
  {
  digitAr[count]++;
  Uint32 prime = sPrimes.getPrimeAt((Uint32)count );

  if( digitAr[count] < (Int32)prime )
    return true; // Nothing more to do.

  digitAr[count] = 0; // It wrapped around.
  // Go around to the next lower digit.
  }

// If it got here then it got to the bottom
// digit without returning and the bottom
// digit wrapped around to zero.
// So that's as far as it can go.
return false;
}
