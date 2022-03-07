// Copyright Eric Chauvin 2021 - 2022.





#include "CrtBuf.h"
#include "../LinuxApi/Casting.h"




CrtBuf::CrtBuf( void )
{
digitAr = new Int32[last];
setToZero();
}



CrtBuf::CrtBuf( const CrtBuf& in )
{
digitAr = new Int32[last];

// setToZero();

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for CrtBuf.\n";
}


CrtBuf::~CrtBuf( void )
{
delete[] digitAr;
}



void CrtBuf::setToZero()
{
for( Int32 count = 0; count < last; count++ )
  digitAr[count] = 0;

}



void CrtBuf::setToOne()
{
for( Int32 count = 0; count < last; count++ )
  digitAr[count] = 1;

}



void CrtBuf::setFromInteger( const Integer& setFrom,
                             IntegerMath& intMath,
                             const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  digitAr[count] = intMath.getMod24( setFrom,
                 sPrimes.getPrimeAt( count ));
  }
}


