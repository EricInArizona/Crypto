// Copyright Eric Chauvin 2021 - 2022.


/*


// The first few numbers for the base:
// 1                  1
// 2                  2
// 3                  6
// 5                 30
// 7                210
// 11             2,310
// 13            30,030
// 17           510,510
// 19         9,699,690
// 23       223,092,870
// 29     6,469,693,230
// 31   200,560,490,130
// 37 7,420,738,134,810




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



void Crt2::copy( const Crt2& toCopy )
{
index = toCopy.index;
const Int32 endAt = index;
for( Int32 count = 0; count <= endAt; count++ )
  digitAr[count] = toCopy.digitAr[count];

}



bool Crt2::isEqual( const Crt2& toCheck ) const
{
if( index != toCheck.index )
  return false;

const Int32 endAt = index;
for( Int32 count = 0; count <= endAt; count++ )
  {
  if( digitAr[count] != toCheck.digitAr[count] )
    return false;

  }

return true;
}



bool Crt2::incAt( const SPrimes& sPrimes,
                  const Int32 where )
{
RangeC::test2( where, 0, index,
             "Crt2::incAt where range." );

for( Int32 count = where; count < last; count++ )
  {
  digitAr[count]++;
  Int32 prime = sPrimes.getPrimeAt( count );

  if( digitAr[count] < prime )
    return true; // Nothing more to do.

  digitAr[count] = 0; // It wrapped around.
  // Go around to the next digit.
  }

// It would never get this far.
return false;
}




void Crt2::toInteger( const CrtMath& crtMath,
                      Integer& toSet,
                      IntegerMath& intMath ) const
{
// Set it to one or zero to start.
toSet.setFromInt24( getD( 0 ));

Integer bigBase;

const Int32 endAt = index;
for( Int32 count = 1; count <= endAt; count++ )
  {
  Int32 digit = getD( count );
  if( digit == 0 )
    continue;

  RangeC::test2( digit, 0, 0xFFFFFF,
            "Crt2.toInteger digit range." );

  crtMath.copyFromIntBuf( bigBase, count );

  // Notice that the prime at this count,
  // at this digit, is not in bigBase yet.
  // sPrimes.getPrimeAt( count ));

  intMath.multiplyInt( bigBase, digit );
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
for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accumDigit = intMath.getMod24(
                                  accum, prime );

  Int32 testDigit = from.getD( count );

  for( Int32 countP = 0; countP < prime;
                                      countP++ )
    {
    crtMath.copyFromIntBuf( bigBase, count );

    // countP might be zero here.
    intMath.multiplyInt( bigBase, countP );

    Int32 test = intMath.getMod24(
                              bigBase, prime );
    test += accumDigit;
    test = test % prime;
    if( test == testDigit )
      {
      if( countP != 0 )
        {
        index = count;
        accum.add( bigBase );
        }

      setD( countP, count );
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
for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accumDigit = intMath.getMod24(
                                  accum, prime );

  Int32 accumD = getAccum( count - 1,
                             count,
                             prime,
                             crtMath );

  if( accumDigit != accumD )
    throw "accumDigit != accumD";


  Int32 testDigit = from.getD( count );

  for( Int32 countP = 0; countP < prime;
                                      countP++ )
    {
    crtMath.copyFromIntBuf( bigBase, count );

    Int32 baseDigit = crtMath.getCrtDigit( count,
                                      count );

    baseDigit = baseDigit * countP;

    // countP might be zero here.
    intMath.multiplyInt( bigBase, countP );

    Int32 test = intMath.getMod24(
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
        index = count;
        accum.add( bigBase );
        }

      setD( countP, count );
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
for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accumD = getAccum( count - 1,
                             count,
                             prime,
                             crtMath );

  Int32 testDigit = from.getD( count );

  for( Int32 countP = 0; countP < prime;
                                      countP++ )
    {
    Int32 baseDigit = crtMath.getCrtDigit( count,
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
        index = count;
        }

      setD( countP, count );
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
for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accumD = getAccum( count - 1,
                             count,
                             prime,
                             crtMath );

  Int32 testDigit = from.getD( count );
  Int32 testD = from.getD( count );

  if( testD < accumD )
    testD += prime;

  testD = testD - accumD;

  // baseD * something = testD

  Int32 baseD = crtMath.getCrtDigit( count,
                                      count );
  if( baseD == 0 )
    throw "baseD == 0";

  Int32 inv = multInv.getInv( count, baseD );
  if( inv == 0 )
    throw "inv == 0";

  // baseD * something = testD
  // baseD * inv = 1
  // baseD * inv * testD = testD

  Int32 testInv = inv * testD;
  testInv = testInv % prime;

  baseD = baseD * inv;
  baseD = baseD % prime;
  if( baseD != 1 )
    throw "baseD != 1";

  for( Int32 countP = 0; countP < prime;
                                      countP++ )
    {
    Int32 baseDigit = crtMath.getCrtDigit( count,
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
        index = count;
        }

      setD( countP, count );
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
for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accumD = getAccum( count - 1,
                             count,
                             prime,
                             crtMath );

  Int32 testD = from.getD( count );

  if( testD < accumD )
    testD += prime;

  testD = testD - accumD;

  Int32 baseD = crtMath.getCrtDigit( count,
                                      count );
  if( baseD == 0 )
    throw "baseD == 0";

  Int32 inv = multInv.getInv( count, baseD );
  if( inv == 0 )
    throw "inv == 0";

  // baseD * inv = 1
  // baseD * inv * testD = testD

  Int32 testInv = inv * testD;
  testInv = testInv % prime;

  if( testInv != 0 )
    {
    index = count;
    }

  setD( testInv, count );
  }
}



void Crt2::setCrt( Crt& toSet,
                   const CrtMath& crtMath,
                   const SPrimes& sPrimes )
{
toSet.setD( getD( 0 ), 0 );

const Int32 top = index;

for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );

  Int32 accumD = getAccum( top, // row
                             count, // column
                             prime,
                             crtMath );

  toSet.setD( accumD, count );
  }
}



bool Crt2::isGoodXAt( const Int32 where,
                  const GoodX& goodX,
                  const CrtMath& crtMath,
                  const SPrimes& sPrimes ) const
{
const Int32 top = index;
Int32 row = top;
if( row > where )
  row = where;

Int32 prime = sPrimes.getPrimeAt( where );

Int32 accumD = getAccum( row, // row
                         where, // column
                         prime,
                         crtMath );

return goodX.getVal( where, accumD );
}




Int32 Crt2::isGoodX( const Int32 start,
                const GoodX& goodX,
                const CrtMath& crtMath,
                const SPrimes& sPrimes ) const
{
// const Int32 top = length;

for( Int32 where = start; where < last; where++ )
  {
  Int32 prime = sPrimes.getPrimeAt( where );

  Int32 accumD = getAccum( where, // row
                           where, // column
                           prime,
                           crtMath );

  if( !goodX.getVal( where, accumD ))
    return where;

  }

return last + 1;
}



bool Crt2::setInvCrt( Crt2& prime2Crt2,
                      const Int32 maxLen,
                      const Crt& prod,
                      const SPrimes& sPrimes,
                      const MultInv& multInv,
                      const CrtMath& crtMath )
{
if( getD( 0 ) == 0 ) // It's an even number.
  return false;

prime2Crt2.setToOne();

const Int32 top = index;

for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );

  Int32 accumD = getAccum( top, // row
                             count, // column
                             prime,
                             crtMath );

  // This will return false if the number is
  // either one of the small primes in a Crt
  // number, or if it is a composite number
  // with at least one factor that is a small
  // prime.

  if( accumD == 0 )
    return false;

  Int32 prodInv = multInv.getInv(
                                count, accumD );
  // accumD * prodInv = 1
  // accumD * (prodInv * prod) = prod

  prodInv = prodInv * prod.getD( count );
  prodInv = prodInv % prime;

  if( !prime2Crt2.setInvDigit( count,
                      prime,
                      prodInv,
                      maxLen,
                      crtMath,
                      multInv ))
    return false;

  }

return true;
}



bool Crt2::setInvDigit( const Int32 where,
                        const Int32 prime,
                        const Int32 fromDigit,
                        const Int32 maxLen,
                        const CrtMath& crtMath,
                        const MultInv& multInv )
{
Int32 accumD = getAccum( where - 1,
                           where,
                           prime,
                           crtMath );

Int32 testD = fromDigit;
if( testD == 0 )
  return false;

if( testD < accumD )
  testD += prime;

testD = testD - accumD;

Int32 baseD = crtMath.getCrtDigit( where,
                                    where );
if( baseD == 0 )
  throw "baseD == 0";

Int32 inv = multInv.getInv( where, baseD );

// baseD * inv = 1
// baseD * (inv * testD) = testD

Int32 testInv = inv * testD;
testInv = testInv % prime;
setD( testInv, where );
if( testInv != 0 )
  index = where;

if( index > maxLen )
  return false;

return true;
}



Str Crt2::toStr( const CrtMath& crtMath,
                 IntegerMath& intMath )
{
Integer showIt;
toInteger( crtMath, showIt, intMath );
Str showS =  intMath.toString10( showIt );
return showS;
}

*/


