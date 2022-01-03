// Copyright Eric Chauvin 2021 - 2022.



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
length = 0;
digitAr[0] = 0;
}



void Crt2::setToOne()
{
length = 0;
digitAr[0] = 1;
}




bool Crt2::isZero()
{
if( length != 0 )
  return false;

if( digitAr[0] != 0 )
  return false;

return true;
}



bool Crt2::isOne()
{
if( length != 0 )
  return false;

if( digitAr[0] != 1 )
  return false;

return true;
}



void Crt2::copy( const Crt2& toCopy )
{
length = toCopy.length;
const Uint32 endAt = length;
for( Uint32 count = 0; count <= endAt; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt2::isEqual( const Crt2& toCheck )
{
if( length != toCheck.length )
  return false;

const Uint32 endAt = length;
for( Uint32 count = 0; count <= endAt; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}


/*
Set the length too.
Start small and go to a bigger number.
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
// So make the length bigger and set the digit
// at the length to 1 and go around again.

return what?;
}
*/


// I could do this for only the bottom 8 bits
// or mod anything.
// Or to a top index below the current index.
void Crt2::toInteger( const CrtMath& crtMath,
                      Integer& toSet,
                      IntegerMath& intMath )
{
// Set it to one or zero to start.
toSet.setFromUInt( (Uint32)getD( 0 ));

Integer bigBase;

const Uint32 endAt = length;
for( Uint32 count = 1; count <= endAt; count++ )
  {
  Uint32 digit = (Uint32)getD( count );
  if( digit == 0 )
    continue;

  crtMath.copyFromIntBuf( bigBase, count );

  // Notice that the prime at this count,
  // at this digit, is not in bigBase yet.
  // sPrimes.getPrimeAt( count ));

  intMath.multiplyUInt( bigBase, digit );
  toSet.add( bigBase );
  }
}



void Crt2::setFromCrt( const Crt& from,
                       Integer& accum,
                       CrtMath& crtMath,
                       SPrimes& sPrimes,
                       IntegerMath& intMath )
{
setFromCrtV1( from, accum, crtMath, sPrimes,
                                    intMath );

// setFromCrtV2( from, crtMath, sPrimes, intMath );
}



// V1 is version 1 for the most basic
// straight-forward version.
void Crt2::setFromCrtV1( const Crt& from,
                         Integer& accum,
                         CrtMath& crtMath,
                         SPrimes& sPrimes,
                         IntegerMath& intMath )
{
if( from.getD( 0 ) == 1 )
  {
  setToOne();
  accum.setToOne();
  }
else
  {
  setToZero();
  accum.setToZero();
  }

Integer bigBase;

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  Uint32 accumDigit = (Uint32)intMath.getMod32(
                                  accum, prime );

  Uint32 testDigit = (Uint32)from.getD( count );

  for( Uint32 countP = 0; countP < prime;
                                      countP++ )
    {
    crtMath.copyFromIntBuf( bigBase, count );

    // countP might be zero here.
    intMath.multiplyUInt( bigBase, countP );

    Uint32 test = (Uint32)intMath.getMod32(
                                bigBase, prime );
    test += accumDigit;
    test = test % prime;
    if( test == testDigit )
      {
      if( countP != 0 )
        {
        length = count;
        accum.add( bigBase );
        }

      setD( (Int32)countP, count );
      break;
      }
    }
  }
}


