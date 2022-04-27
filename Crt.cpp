// Copyright Eric Chauvin 2021 - 2022.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#include "Crt.h"
#include "../CppBase/Casting.h"




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
for( Int32 count = 0; count < last; count++ )
  digitAr[count] = 0;

}



void Crt::setToOne()
{
for( Int32 count = 0; count < last; count++ )
  digitAr[count] = 1;

}



bool Crt::isZero() const
{
for( Int32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 0 )
    return false;

  }

return true;
}



bool Crt::isOne() const
{
for( Int32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 1 )
    return false;

  }

return true;
}



void Crt::copy( const Crt& toCopy )
{
for( Int32 count = 0; count < last; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt::isEqual( const Crt& toCheck ) const
{
for( Int32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}


void Crt::add( const Crt& toAdd,
               const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  // Operations like this could be very fast if
  // they were done on a GPU in parallel.
  digitAr[count] += toAdd.digitAr[count];
  Int32 prime = sPrimes.getPrimeAt( count );
  digitAr[count] = digitAr[count] % prime;
  }
}



void Crt::subtract( const Crt& toSub,
                    const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  digitAr[count] -= toSub.digitAr[count];
  Int32 prime = sPrimes.getPrimeAt( count );

  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



void Crt::decrement( const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  digitAr[count] -= 1;
  Int32 prime = sPrimes.getPrimeAt( count );
  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



void Crt::subtractInt( const Int32 toSub,
                        const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 sub = toSub;
  Int32 prime = sPrimes.getPrimeAt( count );
  sub = sub % prime;
  digitAr[count] -= sub;
  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



void Crt::multiply( const Crt& toMul,
                    const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
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
for( Int32 count = 0; count < last; count++ )
  {
  digitAr[count] = intMath.getMod24( setFrom,
                 sPrimes.getPrimeAt( count ));
  }
}



void Crt::setFromInt( const Int32 setFrom,
                      const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  digitAr[count] = setFrom %
                   sPrimes.getPrimeAt( count );
  }
}
