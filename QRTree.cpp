// Copyright Eric Chauvin 2022.



#include "QRTree.h"
#include "CastE.h"
#include "Division.h"


QRTree::QRTree( void )
{
nodesAr = new QRTreeNode[
                CastE::i32ToU64( last )];
setAllZeros( 0 );
}


QRTree::QRTree( const QRTree& in )
{
nodesAr = new QRTreeNode[
                   CastE::i32ToU64( last )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constr for QRTree.";
}


QRTree::~QRTree( void )
{
delete[] nodesAr;
}


void QRTree::setAllZeros( const Int32 start )
{
for( Int32 count = start; count < last; count++ )
  nodesAr[count].digit = 0;

}


void QRTree::setFirstGoodXAt( const Int32 where,
                   const SPrimes& sPrimes,
                   const GoodX& goodX,
                   const CrtMath& crtMath )
{
if( length < where )
  length = where;

Int32 prime = sPrimes.getPrimeAt( where );

nodesAr[where].digit = 0;
                                    // row, col
Int32 crtDigit = crtMath.getCrtDigit(
                                   where, where );

// nodesAr[0].setAccumByte( 0, 1 );

Int32 accum = getAccum( where - 1,
                        where,
                        prime,
                        crtMath );

for( int count = 0; count < prime; count++ )
  {
  Int32 test = crtDigit * nodesAr[where].digit;
  test  += accum;
  test = test % prime;
  if( goodX.getVal( where, test ))
    return;

  nodesAr[where].digit++;

  if( nodesAr[where].digit >= prime )
    throw "Can this happen? setFirstGoodAt";

  }

throw "Can it get to the bottom? setFirstGoodAt";
}


bool QRTree::setNextGoodXAt( const Int32 where,
                   const SPrimes& sPrimes,
                   const GoodX& goodX,
                   const CrtMath& crtMath )
{
// nodesAr[where].digit has an unknown
// value here.

Int32 prime = sPrimes.getPrimeAt( where );

Int32 crtDigit = crtMath.getCrtDigit(
                                where, where );

Int32 accum = getAccum( where - 1,
                        where,
                        prime,
                        crtMath );

for( int count = 0; count < prime; count++ )
  {
  Int32 test = crtDigit * nodesAr[where].digit;
  test  += accum;
  test = test % prime;
  if( goodX.getVal( where, test ))
    return true;

  nodesAr[where].digit++;
  if( nodesAr[where].digit >= prime )
    return false;

  }

return false;
}



// The x value this is looking for typically
// goes to about the size of the RSA primes
// because both primes are random, which
// means some of the very highest bits will
// be different from each other.  So
// subtracting one prime from the other
// will make bits in x that are about as
// high as the ones in the primes.
// And the 2 in 2x just means one bit at
// the very top.  So it's about the size of
// the RSA primes, give or take a few bits.

// key = (y + x)(y - x)
// If x is small then y, which makes up the
// upper bits of the key,

// key = y^2 - x^2
// key + x^2 = y^2


// RSA public key = p1 * p2
// p1 = y - x
// p2 = y + x
// p2 - p1 = (y + x) - (y - x)
// p2 - p1 = y + x - y + x
// p2 - p1 = 2x
// So if the primes are 1024 bits then
// this will get to somewhere around
// 1024 bits before it finds the answer.
// But this is setting the starting search
// value to 0 or 1.  So it has a long way to
// go before it gets up to the probable size
// of the value it is looking for.
// What is the minimum number the start
// value can be?


void QRTree::setStartValues(
                    const Integer& setpubKeyN,
                    GoodX& goodX,
                    QuadRes& quadRes,
                    const CrtMath& crtMath,
                    IntegerMath& intMath,
                    const SPrimes& sPrimes,
                    const MultInv& multInv,
                    FileIO& mainIO )
{
length = 0;

pubKeyN.copy( setpubKeyN );
prodByte = pubKeyN.getD( 0 ) & 0xFF;

setAllZeros( 0 );

Integer bigX;
getBiggestX( bigX, intMath, sPrimes,
             multInv, crtMath, mainIO );

Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

setupGoodXQuadRes( prod, goodX, sPrimes,
                                   quadRes );

}



bool QRTree::isFullGoodX( const GoodX& goodX,
                const CrtMath& crtMath,
                const SPrimes& sPrimes ) const
{
for( Int32 where = 0; where < last; where++ )
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



void QRTree::setupGoodXQuadRes(
                       Crt& prod,
                       GoodX& goodX,
                       const SPrimes& sPrimes,
                       const QuadRes& quadRes )
{
goodX.setAllFalse( sPrimes );

for( Int32 row = 0; row <
            ProjConst::crtDigitArraySize; row++ )
  {
  Int32 prime = sPrimes.getPrimeAt( row );
  Int32 prodDigit = prod.getD( row );
  for( Int32 col = 0; col < prime; col++ )
    {
    Int32 x = (col * col) + prodDigit;
    x = x % prime;
    // If the x that it makes is a quad res then
    // the original col value is a goodX.
    if( quadRes.getVal( row, x ))
      goodX.setVal( row, col, true );

    }
  }
}



void QRTree::setCrt2( Crt2& toSet )
{
toSet.setLength( length );
for( Int32 count = 0; count <= length; count++ )
  toSet.setD( nodesAr[count].digit, count );

}



bool QRTree::runIt( const GoodX& goodX,
                    const SPrimes& sPrimes,
                    const CrtMath& crtMath,
                    IntegerMath& intMath,
                    FileIO& mainIO )
{
mainIO.appendChars( "Running QRTree tests.\n" );

//  mainIO.appendChars( "Prime1: " );
//  Str showP1 = prime1.toStr( crtMath, intMath );
//  mainIO.appendStr( showP1 );
//  mainIO.appendChars( "\n" );

length = 0;
setFirstGoodXAt( 0, sPrimes, goodX, crtMath );
if( isTheAnswer( goodX, sPrimes, crtMath,
                                  intMath ))
  return true;

// This row only has 0 and 1.
if( testTopRowGoodX( 0, sPrimes, goodX,
                     crtMath, intMath ))
  {
  return true;
  }

for( Int32 branchLength = 1; branchLength < 7;
                               branchLength++ )
  {
  length = branchLength;

  // Start all new at zero.
  setFirstGoodXDepth( 0, sPrimes, goodX,
                                  crtMath );

  // while( true )
  for( Int32 allBranches = 0; allBranches < 10;
                                 allBranches++ )
    {
    if( isTheAnswer( goodX, sPrimes, crtMath,
                                     intMath ))
      return true;
  
    if( testTopRowGoodX( branchLength, sPrimes,
                      goodX, crtMath, intMath ))
      {
      // It found the answer.
      return true;
      }

    bool foundDepth = false;
    for( Int32 depth = branchLength - 1;
                           depth >= 0; depth-- )
      {
      if( setNextGoodXAt( depth, sPrimes,
                              goodX, crtMath ))
        {
        foundDepth = true;
        // Start a new branch above this.
        setFirstGoodXDepth( depth + 1, sPrimes,
                          goodX, crtMath );

        break;
        }
      }

    if( !foundDepth )
      break;

    }

  // If it never found one at the whole depth
  // then it goes around for a new branch
  // length.
  }

mainIO.appendChars(
          "\nWent past the longest branch.\n" );


// I could also keep the accum - 1 value
// for the top row, which is at a particular
// column.

// nodesAr[0].setAccumByte( 0, 1 );

return false;
}


void QRTree::setFirstGoodXDepth(
                      Int32 depth,
                      const SPrimes& sPrimes,
                      const GoodX& goodX,
                      const CrtMath& crtMath )
{
// This has to go from the bottom up because
// the ones at each row depend on the accum
// values from lower rows.
if( depth < 0 )
  depth = 0;

const Int32 max = length;
for( Int32 count = depth; count <= max; count++ )
  {
  setFirstGoodXAt( count, sPrimes, goodX,
                                    crtMath );
  }
}



bool QRTree::testTopRowGoodX( const Int32 where,
                   const SPrimes& sPrimes,
                   const GoodX& goodX,
                   const CrtMath& crtMath,
                   IntegerMath& intMath )
{
Int32 prime = sPrimes.getPrimeAt( where );

for( Int32 count = 0; count < prime; count++ )
  {
  if( !setNextGoodXAt( where, sPrimes, goodX,
                                     crtMath ))
    {
    // No more on this row.
    return false;
    }

  if( isTheAnswer( goodX, sPrimes, crtMath,
                                  intMath ))
    return true;

  }

return false;
}


bool QRTree::isTheAnswer( const GoodX& goodX,
                       const SPrimes& sPrimes,
                       const CrtMath& crtMath,
                       IntegerMath& intMath )
{
=====
Was it this that returned false?

if( isGoodTopAccumByte( crtMath ))
  {
  if( isFullGoodX( goodX, crtMath, sPrimes ))
    {
    Integer sqrRoot;

    if( intMath.squareRoot( pubKeyN, sqrRoot ))
      {
      return true;
      }
    }
  }

return false;
}



void QRTree::getBiggestX( Integer& bigX,
                        IntegerMath& intMath,
                        const SPrimes& sPrimes,
                        const MultInv& multInv,
                        const CrtMath& crtMath,
                        FileIO& mainIO )
{
// What's a bigger number I can use for this?
Int32 bigP = sPrimes.getBiggestPrime();

Integer p1;
Integer p2;
Integer remainder;

p1.setFromInt24( bigP );

Division::divide( pubKeyN, p1, p2,
                    remainder, intMath );

// p1 = y - x
// p2 = y + x
// p2 - p1 = (y + x) - (y - x)
// p2 - p1 = y + x - y + x
// p2 - p1 = 2x
bigX.copy( p2 );
intMath.subtract( bigX, p1 );
bigX.shiftRight( 1 ); // divide by 2.

Crt bigXCrt;
bigXCrt.setFromInteger( bigX, intMath, sPrimes );

bigXCrt2.setFromCrt( bigXCrt, crtMath, sPrimes,
                                     multInv );

mainIO.appendChars( "Biggest X: " );
Str showX = intMath.toString10( bigX );
mainIO.appendStr( showX );
mainIO.appendChars( "\n" );
}
