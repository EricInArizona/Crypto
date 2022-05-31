// Copyright Eric Chauvin 2022.



#include "FindFacSm.h"


FindFacSm::FindFacSm( void )
{
makeSmallAr13();
makeBigAr19();
}


FindFacSm::FindFacSm( const FindFacSm& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The FindFacSm copy"
      " constructor should not be getting"
      " called.";

throw showS;
}


FindFacSm::~FindFacSm( void )
{

}




Int64 FindFacSm::findIt( const Integer& pubKey,
                         const Int64 maxBase,
                         IntegerMath& intMath,
                         const SPrimes& sPrimes )
{
// mainIO.appendChars( "\nFindFacSm started findIt().\n" );

Int32 smallP = intMath.isDivisibleBySmallPrime(
                                pubKey, sPrimes );
if( smallP != 0 )
  return smallP;


Integer sqrRoot;

if( intMath.squareRoot( pubKey, sqrRoot ))
  throw "FindFacSm: It actually has a square root.";


Int64 result = 
        findSmall31( pubKey, maxBase, intMath );

// mainIO.appendChars( "End of FindFacSm.findIt().\n" );

return result;
}



void FindFacSm::makeSmallAr13( void )
{
/*
// Euler's Phi function.
const Int32 phi = (3 - 1) * (5 - 1) * (7 - 1) *
                          (11 - 1) * (13 - 1);

// Phi 13 is: 5760

// mainIO.appendChars( "Phi 13 is: " );
// Str showTest( phi );
// mainIO.appendStr( showTest );
// mainIO.appendChars( "\n" );


smallAr13.clearLastAppend();
if( smallAr13.getArraySize() < phi )
  smallAr13.setSize( phi );

const Int32 max = 2 * 3 * 5 * 7 * 11 * 13;
Int32 howMany = 0;

for( Int32 count = 1; count < max; count += 2 )
  {
  if( (count % 3) == 0 )
    continue;

  if( (count % 5) == 0 )
    continue;

  if( (count % 7) == 0 )
    continue;

  if( (count % 11) == 0 )
    continue;

  if( (count % 13) == 0 )
    continue;

  howMany++;
  smallAr13.appendVal( count );
  }

if( howMany != phi )
  throw "howMany != phi for 13";
*/
}



void FindFacSm::makeBigAr19( void ) // FileIO& mainIO )
{
/*
// Euler's Phi function.
const Int32 phi = (3 - 1) * (5 - 1) * (7 - 1) *
                          (11 - 1) * (13 - 1) *
                          (17 - 1) * (19 - 1);

// Phi 13 is: 5760
// Phi 19 is: 1658880
// Max 19 is: 9699690

// mainIO.appendChars( "Phi 19 is: " );
// Str showTest( phi );
// mainIO.appendStr( showTest );
// mainIO.appendChars( "\n" );

bigAr19.clearLastAppend();
if( bigAr19.getArraySize() < phi )
  bigAr19.setSize( phi );

// const Int32 max = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19;

// mainIO.appendChars( "Max 19 is: " );
// Str showMax( max );
// mainIO.appendStr( showMax );
// mainIO.appendChars( "\n" );

Int32 howMany = 0;

Int32 bigBase = 2 * 3 * 5 * 7 * 11 * 13;

const Int32 last13 = smallAr13.getLastAppend();

for( Int32 countBase = 0; countBase < 17 * 19; countBase++ )
  {
  Int32 basePart = bigBase * countBase;

  for( Int32 count = 0; count < last13; count++ )
    {
    Int32 allParts = basePart + smallAr13.getVal( count );


    if( (allParts % 17) == 0 )
      continue;

    if( (allParts % 19) == 0 )
      continue;

    howMany++;
    bigAr19.appendVal( allParts );
    }
  }

if( howMany != phi )
  throw "howMany != phi for big 19";

*/
}



Int64 FindFacSm::findSmall31( const Integer& pubKey,
                              const Int64 maxBase,
                              IntegerMath& intMath )
{
/*
const Int64 max = 2LL * 3LL * 5LL * 7LL *
       11LL * 13LL * 17LL * 19LL * 23LL *
       29LL * 31LL;

// Max 29 is:   6,469,693,230
// Max 31 is: 200,560,490,130

mainIO.appendChars( "Max 31 is: " );
Str showMax( max );
mainIO.appendStr( showMax );
mainIO.appendChars( "\n" );

// Int64 howMany = 0;

Int64 bigBase = 2L * 3L * 5L * 7L * 11L * 13L * 17L * 19L;

const Int32 last19 = bigAr19.getLastAppend();

for( Int32 countBase = 0; countBase < 23 * 29 * 31;
                                             countBase++ )
  {
  Int64 basePart = bigBase * countBase;

  // Limit the search to not go higher than this.
  if( basePart > maxBase )
    return 0;

  Int32 startAt = 0;
  if( countBase == 0 )
    startAt = 1; // Skip the number 1.

  for( Int32 count = startAt; count < last19; count++ )
    {
    Int64 allParts = basePart + bigAr19.getVal( count );
    // if( allParts == 1 )
      // continue;

    if( (allParts % 23) == 0 )
      continue;

    if( (allParts % 29) == 0 )
      continue;

    if( (allParts % 31) == 0 )
      continue;

    Int64 modTest = intMath.getMod48( pubKey, allParts );
    if( modTest == 0 )
      return allParts;

    }
  }
*/
return 0;
}


