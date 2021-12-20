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



void Crt2::copy( Crt2& toCopy )
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt2::isEqual( Crt2& toCheck )
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}


