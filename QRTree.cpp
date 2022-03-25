// Copyright Eric Chauvin 2022.



#include "../LinuxApi/Casting.h"
#include "../LinuxApi/StIO.h"

#include "QRTree.h"
#include "Division.h"


QRTree::QRTree( void )
{
}



QRTree::QRTree( const QRTree& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constr for QRTree.";
}


QRTree::~QRTree( void )
{
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
                    CrtTreeL& crtTree,
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

Crt3 prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes,
                     multInv,
                     crtMath );

setupGoodXQuadRes( prod, goodX, sPrimes,
                                   quadRes );

crtTree.init( sPrimes, goodX );
}





void QRTree::setupGoodXQuadRes(
                       Crt3& prod,
                       GoodX& goodX,
                       const SPrimes& sPrimes,
                       const QuadRes& quadRes )
{
// goodX.setAllFalse( sPrimes );

for( Int32 row = 0; row <
            ProjConst::crtDigitArraySize; row++ )
  {
  Int32 prime = sPrimes.getPrimeAt( row );
  Int32 prodDigit = prod.crt.getD( row );
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





bool QRTree::runIt( const GoodX& goodX,
                    const SPrimes& sPrimes,
                    const CrtMath& crtMath,
                    const MultInv& multInv,
                    IntegerMath& intMath,
                    CrtTreeL& crtTree,
                    FileIO& mainIO )
{
// Things like goodX are set up in
// setStartValues().

mainIO.appendChars( "QRTree.runIt() started.\n" );

// See if x can be zero or one.
crtTree.setIndex( 0 );
crtTree.setFirstGoodXAt( 0 );

if( isAnswerSlow( sPrimes, crtMath, multInv,
                  intMath, crtTree, mainIO ))
  throw
     "pubKeyN sqr root. Checked with checkEasy.";
  // pubKeyN can't have a square root.



crtTree.setNextGoodXAt( 0 );

if( isAnswerSlow( sPrimes, crtMath, multInv,
                  intMath, crtTree, mainIO ))
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


// Create it here so doesn't get created inside a loop.
Crt3 toCheck;

const Int32 maxBrachIndex = 12;
for( Int32 branchIndex = 1; branchIndex <
                   maxBrachIndex; branchIndex++ )
  {
  crtTree.setIndex( branchIndex );
  Int32 prime = sPrimes.getPrimeAt( branchIndex );

  StIO::printF( "branchIndex is: " );
  StIO::printFD( branchIndex );
  StIO::printF( "\n" );

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
  // crtTree.setFirstGoodXToDepth( 0, goodX );
  crtTree.setFirstGoodXToDepth( 0 );

  Int64 topTests = 0;

  while( true )
    {
    // How many times does testTopRow() get
    // called for each branchIndex?
    topTests++;

    if( testTopRow( branchIndex, sPrimes, multInv,
                    toCheck, crtMath, intMath, crtTree, goodX,
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
      if( crtTree.setNextGoodXAt( depth ))
        {
        crtTree.setFirstGoodXToDepth( depth + 1 );

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




bool QRTree::testBaseByte( Crt3& toCheck,
                           const Int32 accum,
                           const Int32 where,
                           const Int32 baseAccum,
                           const Int32 baseByte,
                           CrtTreeL& crtTree,
                           const Int32 prime,
                           const CrtMath& crtMath,
                           const MultInv& multInv )
{
Int32 topDigit = crtTree.getD( where );

toCheck.crt.setD( topDigit, where );

    // Int32 accumD = getAccum( where - 1, where, prime, crtMath );

toCheck.setFromCrtAt( where, accum, crtMath, prime, multInv );
Int32 mDigit = toCheck.getMD( where );

Int32 testX = baseByte * mDigit;
testX += baseAccum;
testX = testX * testX;
testX = testX & 0xFF;
// testX += pubKeyN.getD( 0 ) & 0xFF;
testX += prodByte;
testX = testX & 0xFF;
return QuadRes::bytesQR( testX );
}





bool QRTree::testTopRow( const Int32 where,
                   const SPrimes& sPrimes,
                   const MultInv& multInv,
                   Crt3& toCheck,
                   const CrtMath& crtMath,
                   IntegerMath& intMath,
                   CrtTreeL& crtTree,
                   const GoodX& goodX,
                   FileIO& mainIO )
{
// Don't run this at length 0.
RangeC::test2( where, 1, last - 1,
              "testTopRow where range." );

Int32 prime = sPrimes.getPrimeAt( where );
// Int32 crtDigit = crtMath.getCrtDigit( where,
   //                                   where );

crtTree.setFirstGoodXAt( where );

toCheck.setFromCrtTree( crtTree, crtMath, sPrimes, multInv );

Int32 baseByte = crtMath.getBaseByte( where );
Int32 baseAccum = toCheck.getAccumByte( where - 1, crtMath );

Int32 accumD = toCheck.getAccum( where - 1, where, prime, crtMath );

if( where == crtTree.getIndex())
  {
  if( testBaseByte( toCheck, accumD, where, baseAccum, baseByte,
      crtTree, prime, crtMath, multInv ))
    {
    if( toCheck.isFullGoodX( goodX, crtMath, sPrimes ))
      {
      if( isAnswerSlow( sPrimes, crtMath, multInv,
                               intMath, crtTree, mainIO ))
        return true;

      }
    }
  }

// The most it could possibly count through.
for( Int32 count = 0; count < prime; count++ )
  {
  if( !crtTree.setNextGoodXAt( where ))
    {
    // No more on this row.
    return false;
    }

  if( testBaseByte( toCheck, accumD, where, baseAccum, baseByte,
                    crtTree, prime, crtMath, multInv ))
    {
    if( toCheck.isFullGoodX( goodX, crtMath, sPrimes ))
      {
      if( isAnswerSlow( sPrimes, crtMath, multInv,
                             intMath, crtTree, mainIO ))
        return true;

      }
    }
  }

return false;
}




bool QRTree::isAnswerSlow( // const GoodX& goodX,
                       const SPrimes& sPrimes,
                       const CrtMath& crtMath,
                       const MultInv& multInv,
                       IntegerMath& intMath,
                       CrtTreeL& crtTree,
                       FileIO& mainIO )
{
Crt3 toCheck;
toCheck.setFromCrtTree( crtTree, crtMath, sPrimes, multInv );

Int32 testIndex = toCheck.getIndex();

// This should have already been found.
if( testIndex < crtTree.getIndex())
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
