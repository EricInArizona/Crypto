// Copyright Eric Chauvin 2021.



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



bool Crt::isZero()
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 0 )
    return false;

  }

return true;
}



bool Crt::isOne()
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != 1 )
    return false;

  }

return true;
}



void Crt::copy( Crt& toCopy )
{
for( Uint32 count = 0; count < last; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt::isEqual( Crt& toCheck )
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}


void Crt::add( Crt& toAdd, SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  // Operations like this could be very fast if
  // they were done on a GPU in parallel.
  digitAr[count] += toAdd.digitAr[count];
  Int32 prime = (Int32)sPrimes.getPrimeAt(
                                     count );
  if( digitAr[count] >= prime )
    digitAr[count] -= prime;

  }
}



void Crt::subtract( Crt& toSub, SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  digitAr[count] -= toSub.digitAr[count];
  if( digitAr[count] < 0 )
    digitAr[count] += (Int32)sPrimes.getPrimeAt(
                                          count );

  }
}



void Crt::decrement( SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  digitAr[count] -= 1;
  if( digitAr[count] < 0 )
    digitAr[count] += (Int32)sPrimes.
                            getPrimeAt( count );
  }
}



void Crt::subtractUint( Uint32 toSub,
                       SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  toSub = toSub % prime;
  digitAr[count] -= toSub;
  if( digitAr[count] < 0 )
    digitAr[count] += prime;

  }
}



/*

  // Copyright Eric Chauvin.
  internal void Multiply( ChineseRemainder ToMul )
    {
    for( int Count = 0; Count < DigitsArraySize; Count++ )
      {
      // There is no Diffusion here either, like the
      // kind that Claude Shannon wrote about in
      // A Mathematical Theory of Cryptography.
      DigitsArray[Count] *= ToMul.DigitsArray[Count];
      DigitsArray[Count] %= (int)IntMath.GetPrimeAt( Count );
      }
    }



  internal void SetFromTraditionalInteger( Integer SetFrom )
    {
    for( int Count = 0; Count < DigitsArraySize; Count++ )
      {
      DigitsArray[Count] = (int)IntMath.GetMod32( SetFrom, IntMath.GetPrimeAt( Count ));
      }
    }



  internal void SetFromUInt( uint SetFrom )
    {
    for( int Count = 0; Count < DigitsArraySize; Count++ )
      {
      DigitsArray[Count] = (int)(SetFrom % (int)IntMath.GetPrimeAt( Count ));
      }
    }



  internal string GetString()
    {
    StringBuilder SBuilder = new StringBuilder();
    for( int Count = 20; Count >= 0; Count-- )
      {
      string ShowS = DigitsArray[Count].ToString() + ", ";
      // DigitsArray[Count].Prime

      SBuilder.Append( ShowS );
      }

    return SBuilder.ToString();
    }


  }
}
*/
