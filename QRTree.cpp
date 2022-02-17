// Copyright Eric Chauvin 2022.



#include "..\\LinuxApi\\Casting.h"

#include "QRTree.h"
#include "Division.h"


QRTree::QRTree( void )
{
// nodesAr = new QRTreeNode[
  //              Casting::i32ToU64( last )];
// setAllZeros( 0 );
}


QRTree::QRTree( const QRTree& in )
{
// nodesAr = new QRTreeNode[
   //                Casting::i32ToU64( last )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constr for QRTree.";
}


QRTree::~QRTree( void )
{
// delete[] nodesAr;
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
                    // const CrtMath& crtMath,
                    IntegerMath& intMath,
                    const SPrimes& sPrimes,
                    // const MultInv& multInv,
                    FileIO& mainIO )
{
mainIO.appendChars( "setStartValues.\n" );

pubKeyN.copy( setpubKeyN );
prodByte = pubKeyN.getD( 0 ) & 0xFF;

/*
  // Do a Crt2.paramIsGreater() for bigX.
  // And lots of other Crt2 math functions.
  // Like multiply and divide and add.

Integer bigX;
getBiggestX( bigX, intMath, sPrimes,
             multInv, crtMath, mainIO );
*/

Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

setupGoodXQuadRes( prod, goodX, sPrimes,
                                   quadRes );
}



/*
bool QRTree::isGoodXAt( const Int32 where,
                const GoodX& goodX,
                const CrtMath& crtMath,
                const SPrimes& sPrimes ) const
{
if( where == 0 )
  return true;

RangeC::test2( where, 1, last - 1,
         "isGoodXAt where range." );

Int32 prime = sPrimes.getPrimeAt( where );

Int32 accumD = getAccum( where, // row
                         where, // column
                         prime,
                         crtMath );

return goodX.getVal( where, accumD );
}



bool QRTree::isFullGoodX2( const GoodX& goodX,
                const CrtMath& crtMath,
                const SPrimes& sPrimes ) const
{
// Both 0 and 1 are quad residues mod 2
// so start at 1.
for( Int32 where = 1; where < last; where++ )
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


void QRTree::setupGoodXQuadRes(
                       Crt& prod,
                       GoodX& goodX,
                       const SPrimes& sPrimes,
                       const QuadRes& quadRes )
{
// goodX.setAllFalse( sPrimes );

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



/*
void QRTree::setCrt2( Crt2& toSet )
{
toSet.setIndex( index );

// Set these to what?
// for( Int32 count = 0; count <= index; count++ )
  // toSet.setD( 0, count );

}
*/



bool QRTree::runIt( const GoodX& goodX,
                    const SPrimes& sPrimes,
                    const CrtMath& crtMath,
                    const MultInv& multInv,
                    IntegerMath& intMath,
                    FileIO& mainIO )
{
// Things like goodX are set up in
// setStartValues().

mainIO.appendChars( "QRTree.runIt() started.\n" );

// See if x can be zero or one.
crtTree.setIndex( 0 );
crtTree.setFirstGoodXAt( 0, goodX );

if( isAnswerSlow( sPrimes, crtMath, multInv,
                  intMath, mainIO ))
  throw
     "pubKeyN sqr root. Checked with checkEasy.";
  // pubKeyN can't have a square root.



crtTree.setNextGoodXAt( 0, goodX );

if( isAnswerSlow( sPrimes, crtMath, multInv,
                  intMath, mainIO ))
  {
  mainIO.appendChars( "Found at x = 1.\n" );
  return true;
  }

mainIO.appendChars( "\nTop of loop.\n" );

// See the comments in isAnswerSlow() about the
// highest branchIndex this can go to in a
// reasonable time with just iterating through
// it alone.  The number of loops goes like:
// branchIndex is: 1
// topTests: 2
// ...
// branchIndex is: 6
// topTests: 2700
// branchIndex is: 7
// topTests: 24300
// branchIndex is: 8
// topTests: 243000
// branchIndex is: 9
// topTests: 2916000
// branchIndex is: 10
// topTests: 40824000

const Int32 maxBrachIndex = 10;
for( Int32 branchIndex = 1; branchIndex <
                   maxBrachIndex; branchIndex++ )
  {
  crtTree.setIndex( branchIndex );
  Int32 prime = sPrimes.getPrimeAt(
                                branchIndex );

  mainIO.appendChars(  "branchIndex is: " );
  Str showB( branchIndex );
  mainIO.appendStr( showB );
  mainIO.appendChars(  "\n" );

  mainIO.appendChars(  "Branch prime is: " );
  Str showP( prime );
  mainIO.appendStr( showP );
  mainIO.appendChars(  "\n" );

  // Start all new at zero.
  // This goes up to index.
  crtTree.setFirstGoodXToDepth( 0, goodX );

  Int64 topTests = 0;
  // for( Int32 allBranches = 0;
    //    allBranches < 10000; allBranches++ )

  while( true )
    {
    // How many times does testTopRow() get
    // called for each branchIndex?
    topTests++;

    if( testTopRow( branchIndex, sPrimes, multInv,
                    goodX, crtMath, intMath,
                    mainIO ))
      {
      mainIO.appendChars(  "\nFound it.\n" );
      mainIO.appendChars(  "topTests: " );
      Str showS( topTests );
      mainIO.appendStr( showS );
      mainIO.appendChars(  "\n" );

      // It found the answer.
      return true;
      }

    bool foundDepth = false;

    for( Int32 depth = branchIndex - 1;
                           depth >= 0; depth-- )
      {
      if( crtTree.setNextGoodXAt( depth, goodX ))
        {
        crtTree.setFirstGoodXToDepth( depth + 1,
                                      goodX );

        foundDepth = true;
        break;
        }
      }

    if( !foundDepth )
      break;

    }

  mainIO.appendChars(  "topTests: " );
  Str showS( topTests );
  mainIO.appendStr( showS );
  mainIO.appendChars(  "\n\n" );

  // If it never found one at the whole depth
  // then it goes around for a new branch
  // length.
  }

mainIO.appendChars(
          "\nWent past the longest branch.\n" );

return false;
}



bool QRTree::testTopRow( const Int32 where,
                   const SPrimes& sPrimes,
                   const MultInv& multInv,
                   const GoodX& goodX,
                   const CrtMath& crtMath,
                   IntegerMath& intMath,
                   FileIO& mainIO )
{
// Don't run this at length 0.
RangeC::test2( where, 1, last - 1,
              "testTopRow where range." );

Int32 prime = sPrimes.getPrimeAt( where );
// Int32 crtDigit = crtMath.getCrtDigit( where,
   //                                   where );

crtTree.setFirstGoodXAt( where, goodX );

if( isAnswerSlow( sPrimes, crtMath, multInv,
                         intMath, mainIO ))
  return true;

// The most it could possibly count through.
for( Int32 count = 0; count < prime; count++ )
  {
  if( !crtTree.setNextGoodXAt( where, goodX ))
    {
    // No more on this row.
    return false;
    }

  if( isAnswerSlow( sPrimes, crtMath, multInv,
                           intMath, mainIO ))
    return true;

  }

return false;
}



// See Crt2::setFromCrtV5().
// And earlier versions like V1, V2, etc.

void QRTree::setFromCrtTree( Crt2& toSet,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     const MultInv& multInv )
{
// Int32 keepAccum =
// Crt2::setFromCrtV5() has the old reduncancy.
// Make a V6.
// Make a separate V6 of this too.

if( crtTree.getD( 0 ) == 1 )
  {
  // Int32 keepAccum =
  toSet.setToOne();
  }
else
  {
  // Int32 keepAccum =
  toSet.setToZero();
  }

const Int32 max = crtTree.getIndex();

// Int32 keepAccum =
// Count starts at 1, so it's the prime 3.
for( Int32 count = 1; count <= max; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  Int32 accumD = toSet.getAccum( count - 1,
                             count,
                             prime,
                             crtMath );

  // Int32 keepAccum = keep the last one it got.

  Int32 testD = crtTree.getD( count );

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
  // baseD * (inv * testD) = testD

  Int32 testInv = inv * testD;
  testInv = testInv % prime;

  if( testInv != 0 )
    {
    // The toSet.index can't go higher than
    // count.  But it can be lower.

    // It is likely not quad res at higher
    // index values.  So doing isFullGoodX()
    // would be doing accum only up to the
    // index.  getAccum() has a top at index.

    toSet.setIndex( count );
    }

  toSet.setD( testInv, count );
  }
}



bool QRTree::isAnswerSlow( // const GoodX& goodX,
                       const SPrimes& sPrimes,
                       const CrtMath& crtMath,
                       const MultInv& multInv,
                       IntegerMath& intMath,
                       FileIO& mainIO )
{
// Comment out this whole function except for
// returning false, and see how long it takes to
// just iterate through the CrtTree.
// return false;

Crt2 toCheck;
setFromCrtTree( toCheck, crtMath, sPrimes,
                multInv );

Int32 testIndex = toCheck.getIndex();

// This happens.
// if( testIndex < crtTree.getIndex())
  // throw "This should have already been found.";

Int32 theByte = toCheck.getAccumByte( testIndex,
                                      crtMath );

Int32 testX = theByte * theByte;
testX += pubKeyN.getD( 0 ) & 0xFF;
testX = testX & 0xFF;
if( !QuadRes::bytesQR( testX ))
  return false;


// The index on toSet can be lower than the
// index on the CrtTree because the digits
// above a certain point can be zero, but
// the accum value makes it the right Crt
// value.

// The crudest way to test this.
Integer x;
Integer y;
Integer ySquared;

toCheck.toInteger( crtMath, x, intMath );
ySquared.copy( x );
intMath.square( ySquared );
ySquared.add( pubKeyN );

if( !intMath.squareRoot( ySquared, y ))
  {
  // mainIO.appendChars(
  //                 "False on square root.\n" );
  return false;
  }

mainIO.appendChars( "True on square root.\n" );

Integer prime1;
prime1.copy( y );
prime1.add( x );

Integer prime2;
prime2.copy( y );
intMath.subtract( prime2, x );
if( prime2.isOne())
  {
  mainIO.appendChars(
                   "Answer prime2 is 1.\n" );

  return false;
  }

return true;


/*

if( !isFullGoodX2( goodX, crtMath, sPrimes ))
  return false;

mainIO.appendChars( "isFullGood.\n" );
mainIO.appendChars(
             "It gets here once or twice.\n" );

Integer x;
Integer y;
Integer ySquared;

Crt2 xCrt2;
setCrt2( xCrt2 );
xCrt2.toInteger( crtMath, x, intMath );
ySquared.copy( x );
intMath.square( ySquared );
ySquared.add( pubKeyN );

mainIO.appendChars(  "ySquared: " );
Str showS =  intMath.toString10( ySquared );
mainIO.appendStr( showS );
mainIO.appendChars(  "\n" );

if( !intMath.squareRoot( ySquared, y ))
  {
  mainIO.appendChars(
                   "False on square root.\n" );
  return false;
  }

mainIO.appendChars( "True on square root.\n" );

Integer prime1;
prime1.copy( y );
prime1.add( x );

Integer prime2;
prime2.copy( y );
intMath.subtract( prime2, x );
if( prime2.isOne())
  {
  mainIO.appendChars(
                   "Answer prime2 is 1.\n" );

  return false;
  }

return true;
*/
}




/*
void QRTree::getBiggestX( Integer& bigX,
                        IntegerMath& intMath,
                        const SPrimes& sPrimes,
                        const MultInv& multInv,
                        const CrtMath& crtMath,
                        FileIO& mainIO )
{
// What's a bigger number I can use for this?
// Int32 bigP = sPrimes.getBiggestPrime();
Int32 bigP = 2;

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
bigXCrt.setFromInteger( bigX, intMath,
                                  sPrimes );

bigXCrt2.setFromCrt( bigXCrt, crtMath, sPrimes,
                                     multInv );

mainIO.appendChars( "Biggest X: " );
Str showX = intMath.toString10( bigX );
mainIO.appendStr( showX );
mainIO.appendChars( "\n" );
}
*/
