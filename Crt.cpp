// Copyright Eric Chauvin 2021 - 2022.



#include "Crt.h"


// A lot of these things could be very fast if
// they are done on a GPU.  A loop like this:
// for( Uint32 count = 0; count < last; count++ )
//  digitAr[count] = 0;
// Could be done independently for each value
// on a GPU.


Crt::Crt( void )
{
digitAr = new Int32[last];
setToZero();
}


Crt::Crt( const Crt& in )
{
digitAr = new Int32[last];

// setToZero();

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for Crt.\n";
}


Crt::~Crt( void )
{
delete[] digitAr;
}



void Crt::setToZero()
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = 0;

}



void Crt::setToOne()
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = 1;

}



bool Crt::isZero() const
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 0 )
    return false;

  }

return true;
}



bool Crt::isOne() const
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 1 )
    return false;

  }

return true;
}



void Crt::copy( const Crt& toCopy )
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt::isEqual( const Crt& toCheck ) const
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}


void Crt::add( const Crt& toAdd,
               const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  // Operations like this could be very fast if
  // they were done on a GPU in parallel.
  digitAr[count] += toAdd.digitAr[count];
  Int32 prime = (Int32)sPrimes.getPrimeAt(
                                     count );
  digitAr[count] = digitAr[count] % prime;
  }
}



void Crt::subtract( const Crt& toSub,
                    const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  digitAr[count] -= toSub.digitAr[count];
  Int32 prime = (Int32)sPrimes.getPrimeAt(
                                     count );

  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



void Crt::decrement( const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  digitAr[count] -= 1;
  Int32 prime = (Int32)sPrimes.getPrimeAt(
                                     count );
  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



void Crt::subtractUint( const Uint32 toSub,
                        const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  Int32 sub = (Int32)toSub;
  Int32 prime = (Int32)sPrimes.getPrimeAt( count );
  sub = sub % prime;
  digitAr[count] -= sub;
  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



void Crt::multiply( const Crt& toMul,
                    const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  // This beats the Karatsuba Multiplication
  // algorithm easily.  It can be done on a GPU
  // too.

  digitAr[count] *= toMul.digitAr[count];
  digitAr[count] %= sPrimes.getPrimeAt( count );
  }
}



void Crt::setFromInteger( const Integer& setFrom,
                          IntegerMath& intMath,
                          const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  digitAr[count] = (Int32)intMath.getMod32(
           setFrom, sPrimes.getPrimeAt( count ));
  }
}



void Crt::setFromUInt( const Uint32 setFrom,
                       const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  digitAr[count] = (Int32)setFrom %
              (Int32)sPrimes.getPrimeAt( count );
  }
}
