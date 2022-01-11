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



void Crt2::setToIndex1( const Uint32 index )
{
length = index;
digitAr[0] = 1;

for( Uint32 count = 1; count <= index; count++ )
  {
  digitAr[index] = 0;
  }
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


bool Crt2::incRev( SPrimes& sPrimes,
                   const Uint32 top )
{
// Change the digits from the top so that
// lower accumulate values can stay the same.

for( Int32 count = (Int32)top; count >= 0; count-- )
  {
  digitAr[count]++;
  Uint32 prime = sPrimes.getPrimeAt((Uint32)count );

  if( digitAr[count] < (Int32)prime )
    return true; // Nothing more to do.

  digitAr[count] = 0; // It wrapped around.
  // Go around to the next lower digit.


  }

return false;
}



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
                       // Integer& accum,
                       CrtMath& crtMath,
                       SPrimes& sPrimes,
                       // IntegerMath& intMath
                       MultInv& multInv
                       )
{
// setFromCrtV1( from, accum, crtMath, sPrimes,
//                                    intMath );

// setFromCrtV2( from, accum, crtMath, sPrimes,
//                                    intMath );

// setFromCrtV3( from, crtMath, sPrimes );

// setFromCrtV4( from, crtMath, sPrimes, multInv );
setFromCrtV5( from, crtMath, sPrimes, multInv );
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



Uint32 Crt2::getAccumD( const Uint32 row,
                        const Uint32 col,
                        const Uint32 prime,
                        CrtMath& crtMath )
{
// It is either zero or one.
Uint32 result = (Uint32)getD( 0 );

for( Uint32 count = 1; count <= row; count++ )
  {
  Uint32 accum = crtMath.getCrtDigit( count,
                                      col );
  accum = accum * (Uint32)getD( count );
  result += accum;
  result = result % prime;
  }

return result;
}



void Crt2::setFromCrtV2( const Crt& from,
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

  Uint32 accumD = getAccumD( count - 1,
                             count,
                             prime,
                             crtMath );

  if( accumDigit != accumD )
    throw "accumDigit != accumD";


  Uint32 testDigit = (Uint32)from.getD( count );

  for( Uint32 countP = 0; countP < prime;
                                      countP++ )
    {
    crtMath.copyFromIntBuf( bigBase, count );

    Uint32 baseDigit = crtMath.getCrtDigit( count,
                                      count );

    baseDigit = baseDigit * countP;

    // countP might be zero here.
    intMath.multiplyUInt( bigBase, countP );

    Uint32 test = (Uint32)intMath.getMod32(
                                bigBase, prime );

    baseDigit = baseDigit % prime;
    if( baseDigit != test )
      throw "baseDigit != test";

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




void Crt2::setFromCrtV3( const Crt& from,
                         CrtMath& crtMath,
                         SPrimes& sPrimes )
{
if( from.getD( 0 ) == 1 )
  setToOne();
else
  setToZero();

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  Uint32 accumD = getAccumD( count - 1,
                             count,
                             prime,
                             crtMath );

  Uint32 testDigit = (Uint32)from.getD( count );

  for( Uint32 countP = 0; countP < prime;
                                      countP++ )
    {
    Uint32 baseDigit = crtMath.getCrtDigit( count,
                                      count );

    baseDigit = baseDigit * countP;

    // countP might be zero here.

    baseDigit = baseDigit % prime;
    baseDigit += accumD;
    baseDigit = baseDigit % prime;
    if( baseDigit == testDigit )
      {
      if( countP != 0 )
        {
        length = count;
        }

      setD( (Int32)countP, count );
      break;
      }
    }
  }
}



void Crt2::setFromCrtV4( const Crt& from,
                         CrtMath& crtMath,
                         SPrimes& sPrimes,
                         MultInv& multInv )
{
if( from.getD( 0 ) == 1 )
  setToOne();
else
  setToZero();

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  Uint32 accumD = getAccumD( count - 1,
                             count,
                             prime,
                             crtMath );

  Uint32 testDigit = (Uint32)from.getD( count );
  Uint32 testD = (Uint32)from.getD( count );

  if( testD < accumD )
    testD += prime;

  testD = testD - accumD;

  // baseD * something = testD

  Uint32 baseD = crtMath.getCrtDigit( count,
                                      count );
  if( baseD == 0 )
    throw "baseD == 0";

  Uint32 inv = multInv.getInv( count, baseD );
  if( inv == 0 )
    throw "inv == 0";

  // baseD * something = testD
  // baseD * inv = 1
  // baseD * inv * testD = testD

  Uint32 testInv = inv * testD;
  testInv = testInv % prime;

  baseD = baseD * inv;
  baseD = baseD % prime;
  if( baseD != 1 )
    throw "baseD != 1";

  for( Uint32 countP = 0; countP < prime;
                                      countP++ )
    {
    Uint32 baseDigit = crtMath.getCrtDigit( count,
                                      count );
    baseDigit = baseDigit * countP;

    // countP might be zero here.
    baseDigit += accumD;
    baseDigit = baseDigit % prime;
    if( baseDigit == testDigit )
      {
      if( testInv != countP )
        throw "testInv != countP";

      if( countP != 0 )
        {
        length = count;
        }

      setD( (Int32)countP, count );
      break;
      }
    }
  }
}



void Crt2::setFromCrtV5( const Crt& from,
                         CrtMath& crtMath,
                         SPrimes& sPrimes,
                         MultInv& multInv )
{
if( from.getD( 0 ) == 1 )
  setToOne();
else
  setToZero();

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  Uint32 accumD = getAccumD( count - 1,
                             count,
                             prime,
                             crtMath );

  Uint32 testD = (Uint32)from.getD( count );

  if( testD < accumD )
    testD += prime;

  testD = testD - accumD;

  Uint32 baseD = crtMath.getCrtDigit( count,
                                      count );
  if( baseD == 0 )
    throw "baseD == 0";

  Uint32 inv = multInv.getInv( count, baseD );
  if( inv == 0 )
    throw "inv == 0";

  // baseD * inv = 1
  // baseD * inv * testD = testD

  Uint32 testInv = inv * testD;
  testInv = testInv % prime;

  if( testInv != 0 )
    {
    length = count;
    }

  setD( (Int32)testInv, count );
  }
}



void Crt2::setCrt( Crt& toSet,
                   CrtMath& crtMath,
                   SPrimes& sPrimes )
{
toSet.setD( getD( 0 ), 0 );

const Uint32 top = length;

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );

  Uint32 accumD = getAccumD( top, // row
                             count, // column
                             prime,
                             crtMath );

  toSet.setD( (Int32)accumD, count );
  }
}



bool Crt2::setInvCrt( Crt& crt,
                      Crt& inv,
                      SPrimes& sPrimes,
                      MultInv& multInv,
                      CrtMath& crtMath )
{
if( getD( 0 ) == 0 )
  return false;

crt.setD( 1, 0 );
inv.setD( 1, 0 );

const Uint32 top = length;

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );

  Uint32 accumD = getAccumD( top, // row
                             count, // column
                             prime,
                             crtMath );

  if( accumD == 0 )
    return false;

  crt.setD( (Int32)accumD, count );
  inv.setD( (Int32)multInv.getInv(
                        count, accumD ), count );
  }

return true;
}
