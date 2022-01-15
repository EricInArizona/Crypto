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



bool Crt2::increment( const SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  if( length < count )
    {
    length = count;
    digitAr[count] = 0;
    }

  digitAr[count]++;
  Uint32 prime = sPrimes.getPrimeAt( count );

  if( digitAr[count] < (Int32)prime )
    return true; // Nothing more to do.

  digitAr[count] = 0; // It wrapped around.
  // Go around to the next digit.
  }

return false;
}



bool Crt2::incAt( const SPrimes& sPrimes,
                            const Uint32 where )
{
if( (length + 1) < where )
  throw "(length + 1) < where";

for( Uint32 count = where; count < last; count++ )
  {
  if( length < count )
    {
    length = count;
    digitAr[count] = 0;
    }

  digitAr[count]++;
  Uint32 prime = sPrimes.getPrimeAt( count );

  if( digitAr[count] < (Int32)prime )
    return true; // Nothing more to do.

  digitAr[count] = 0; // It wrapped around.
  // Go around to the next digit.
  }

return false;
}



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
                       const CrtMath& crtMath,
                       const SPrimes& sPrimes,
                       // IntegerMath& intMath
                       const MultInv& multInv
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
                         const CrtMath& crtMath,
                         const SPrimes& sPrimes,
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



void Crt2::setFromCrtV2( const Crt& from,
                         Integer& accum,
                         const CrtMath& crtMath,
                         const SPrimes& sPrimes,
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
                         const CrtMath& crtMath,
                         const SPrimes& sPrimes )
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
                         const CrtMath& crtMath,
                         const SPrimes& sPrimes,
                         const MultInv& multInv )
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
                         const CrtMath& crtMath,
                         const SPrimes& sPrimes,
                         const MultInv& multInv )
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
                   const CrtMath& crtMath,
                   const SPrimes& sPrimes )
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
                      Crt2& prime2Crt2,
                      const Uint32 maxLen,
                      const Crt& prod,
                      const SPrimes& sPrimes,
                      const MultInv& multInv,
                      const CrtMath& crtMath )
{
if( getD( 0 ) == 0 )
  return false;

crt.setToOne();
inv.setToOne();
prime2Crt2.setToOne();

const Uint32 top = length;

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );

  Uint32 accumD = getAccumD( top, // row
                             count, // column
                             prime,
                             crtMath );

  // This will return false if the number is
  // either one of the small primes in a Crt
  // number, or if it is a composite number
  // with at least one factor that is a small
  // prime.  So if the biggest prime in a Crt
  // number is 3691, then the first number
  // after 1 that it returns true on is 3697.

  if( accumD == 0 )
    return false;

  crt.setD( (Int32)accumD, count );
  Uint32 prodInv = multInv.getInv(
                                count, accumD );
  // accumD * prodInv = 1
  // accumD * (prodInv * prod) = prod

  prodInv = prodInv * (Uint32)prod.getD( count );
  prodInv = prodInv % prime;

  inv.setD( (Int32)prodInv, count );

  if( !prime2Crt2.setInvDigit( count,
                      prime,
                      (Uint32)inv.getD( count ),
                      maxLen,
                      crtMath,
                      multInv ))
    return false;

  }

return true;
}



/*
bool Crt2::setPrimeFactor( const Crt& from,
                           const Uint32 maxLen,
                           const CrtMath& crtMath,
                           const SPrimes& sPrimes,
                           const MultInv& multInv )
{
setToOne();

// Count starts at 1, so it's the prime 3.
for( Uint32 count = 1; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );

  if( !setInvDigit( count, prime,
               (Uint32)from.getD( count ),
               maxLen,
               crtMath,
               multInv ))
    return false;

  }

return true;
}
*/



bool Crt2::setInvDigit( const Uint32 where,
                        const Uint32 prime,
                        const Uint32 fromDigit,
                        const Uint32 maxLen,
                        const CrtMath& crtMath,
                        const MultInv& multInv )
{
Uint32 accumD = getAccumD( where - 1,
                           where,
                           prime,
                           crtMath );

Uint32 testD = fromDigit;
if( testD == 0 )
  return false;

if( testD < accumD )
  testD += prime;

testD = testD - accumD;

Uint32 baseD = crtMath.getCrtDigit( where,
                                    where );
if( baseD == 0 )
  throw "baseD == 0";

Uint32 inv = multInv.getInv( where, baseD );

// baseD * inv = 1
// baseD * (inv * testD) = testD

Uint32 testInv = inv * testD;
testInv = testInv % prime;
setD( (Int32)testInv, where );
if( testInv != 0 )
  length = where;

if( length > maxLen )
  return false;

return true;
}
