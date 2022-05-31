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




#include "Crt3.h"




Crt3::Crt3( void )
{
digitMAr = new Int32[last];
setToZero();
}


Crt3::Crt3( const Crt3& in )
{
digitMAr = new Int32[last];

// setToZero();

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for Crt3.\n";
}


Crt3::~Crt3( void )
{
delete[] digitMAr;
}



void Crt3::copy( const Crt3& toCopy )
{
index = toCopy.index;
const Int32 endAt = index;
for( Int32 count = 0; count <= endAt; count++ )
  {
  digitMAr[count] = toCopy.digitMAr[count];
  }
}



/////////
void Crt3::copyToCrtBuf( CrtBuf& copyTo )
{
for( Int32 count = 0; count < last; count++ )
  {
  copyTo.setD( crt.getD( count ), count );
  }
}
//////



bool Crt3::isEqual( const Crt3& toCheck ) const
{
if( index != toCheck.index )
  return false;

const Int32 endAt = index;
for( Int32 count = 0; count <= endAt; count++ )
  {
  if( digitMAr[count] != toCheck.digitMAr[count] )
    return false;

  }

return true;
}



/////////
bool Crt3::incAt( const SPrimes& sPrimes,
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
/////




void Crt3::toInteger( const CrtMath& crtMath,
                      Integer& toSet,
                      IntegerMath& intMath ) const
{
// Set it to one or zero to start.
toSet.setFromInt24( getMD( 0 ));

Integer bigBase;

const Int32 endAt = index;
for( Int32 count = 1; count <= endAt; count++ )
  {
  Int32 digit = getMD( count );
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





// See Crt2 for versions 1 through 4.
// V1 is version 1 for the most basic
// straight-forward version.


void Crt3::setFromCrtV6( const Int32 maxIndex,
                         const CrtMath& crtMath,
                         const SPrimes& sPrimes,
                         const MultInv& multInv )
{
if( crt.getD( 0 ) == 1 )
  setToOne();
else
  setToZero();

// Count starts at 1, so it's the prime 3.
for( Int32 count = 1; count <= maxIndex; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accum = getAccum( count - 1, count, prime, crtMath );

  setFromCrtAt( count, accum, crtMath, prime, multInv );

  if( digitMAr[count] != 0 )
    {
    index = count;
    }
  }
}




void Crt3::setCrt( const CrtMath& crtMath,
                   const SPrimes& sPrimes )
{
crt.setD( getMD( 0 ), 0 );

const Int32 top = index;

for( Int32 count = 1; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );

  Int32 accumD = getAccum( top, // row
                             count, // column
                             prime,
                             crtMath );

  crt.setD( accumD, count );
  }
}




////
bool Crt3::setInvCrt( Crt3& prime2Crt3,
                      const Int32 maxLen,
                      const Crt& prod,
                      const SPrimes& sPrimes,
                      const MultInv& multInv,
                      const CrtMath& crtMath )
{
if( getCrtD( 0 ) == 0 ) // It's an even number.
  return false;

prime2Crt3.setToOne();

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
///////



////
bool Crt3::setInvDigit( const Int32 where,
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
//////



Str Crt3::toStr( const CrtMath& crtMath,
                 IntegerMath& intMath )
{
Integer showIt;
toInteger( crtMath, showIt, intMath );
Str showS =  intMath.toString10( showIt );
return showS;
}





void Crt3::setFromInteger( const Integer& setFrom,
                           IntegerMath& intMath,
                           const SPrimes& sPrimes,
                           const MultInv& multInv,
                           const CrtMath& crtMath )
{
crt.setFromInteger( setFrom, intMath, sPrimes );

setFromCrtV6( last - 1, crtMath, sPrimes, multInv );
}




////
void Crt::setFromInt( const Int32 setFrom,
                      const SPrimes& sPrimes )
{
for( Int32 count = 0; count < last; count++ )
  {
  digitAr[count] = setFrom %
                   sPrimes.getPrimeAt( count );
  }
}

/////



/////
void Crt3::setFromCrtTree( const CrtTreeL& crtTree,
                           const CrtMath& crtMath,
                           const SPrimes& sPrimes,
                           const MultInv& multInv )
{
const Int32 max = crtTree.getIndex();
index = max;

for( Int32 count = 0; count <= max; count++ )
  {
  crt.setD( crtTree.getD( count ), count );
  }

setFromCrtV6( max, crtMath, sPrimes, multInv );
}
/////



bool Crt3::isFullGoodX( const GoodX& goodX,
                        const CrtMath& crtMath,
                        const SPrimes& sPrimes ) const
{
const Int32 startAt = index + 1;
for( Int32 where = startAt; where < last; where++ )
  {
  Int32 prime = sPrimes.getPrimeAt( where );

  Int32 accumD = getAccum( where, // row
                           where, // column
                           prime,
                           crtMath );

  if( !goodX.getVal( where, accumD ))
    return false;

  }

return true;
}

*/
