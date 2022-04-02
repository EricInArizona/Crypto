// Copyright Eric Chauvin 2022.




#include "FindFacQr.h"
#include "../LinuxApi/Casting.h"


FindFacQr::FindFacQr( void )
{

}



FindFacQr::FindFacQr( const FindFacQr& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

const char* showS = "The FindFacQr copy"
      " constructor should not be getting"
      " called.";

throw showS;
}


FindFacQr::~FindFacQr( void )
{

}




bool FindFacQr::findIt( const Integer& pubKey,
                        Integer& prime1,
                        Integer& prime2,
                        IntegerMath& intMath,
                        SPrimes& sPrimes,
                        FileIO& mainIO )
{
mainIO.appendChars( "\nFindFacQr started findIt().\n" );

quadRes.init( sPrimes, mainIO );

// This would have already been checked by FindFacSm,
// so it doesn't have any small prime factors.

makeSmallAr17( pubKey, intMath, mainIO );

makeBigAr23( pubKey, intMath, mainIO );


if( !findQr29( pubKey, prime1, prime2, intMath, mainIO ))
  {
  mainIO.appendChars( "\nFindQr returned false.\n" );
  return false;
  }


mainIO.appendChars( "prime1: " );
Str showP1 = intMath.toString10( prime1 );
mainIO.appendStr( showP1 );
mainIO.appendChars( "\n" );

mainIO.appendChars( "prime2: " );
Str showP2 = intMath.toString10( prime2 );
mainIO.appendStr( showP2 );
mainIO.appendChars( "\n" );

return true;
}




void FindFacQr::makeSmallAr17( const Integer& pubKey,
                               IntegerMath& intMath,
                               FileIO& mainIO )
{
mainIO.appendChars( "makeSmallAr17\n" );

smallAr17.clearLastAppend();
//  smallAr17.setSize( phi );


Int32 pKeyMod3 = intMath.getMod24( pubKey, 3 );
Int32 pKeyMod5 = intMath.getMod24( pubKey, 5 );
Int32 pKeyMod7 = intMath.getMod24( pubKey, 7 );
Int32 pKeyMod11 = intMath.getMod24( pubKey, 11 );
Int32 pKeyMod13 = intMath.getMod24( pubKey, 13 );
Int32 pKeyMod17 = intMath.getMod24( pubKey, 17 );


const Int32 max = 2 * 3 * 5 * 7 * 11 * 13 * 17;
Int32 howMany = 0;

for( Int32 count = 0; count < max; count++ )
  {
  if( !isGoodX( count, pKeyMod3, 3, 1 ))
    continue;

  if( !isGoodX( count, pKeyMod5, 5, 2 ))
    continue;

  if( !isGoodX( count, pKeyMod7, 7, 3 ))
    continue;

  if( !isGoodX( count, pKeyMod11, 11, 4 ))
    continue;

  if( !isGoodX( count, pKeyMod13, 13, 5 ))
    continue;

  if( !isGoodX( count, pKeyMod17, 17, 6 ))
    continue;

  howMany++;
  smallAr17.appendVal( count );
  }


// This varies a lot with the pubKey.
// howMany for 17 is: 12096

mainIO.appendChars( "howMany for 17 is: " );
Str showTest( howMany );
mainIO.appendStr( showTest );
mainIO.appendChars( "\n" );
}



void FindFacQr::makeBigAr23( const Integer& pubKey,
                             IntegerMath& intMath,
                             FileIO& mainIO )
{
mainIO.appendChars( "makeBigAr23\n" );


bigAr23.clearLastAppend();
//  bigAr23.setSize( phi );

Int32 pKeyMod19 = intMath.getMod24( pubKey, 19 );
Int32 pKeyMod23 = intMath.getMod24( pubKey, 23 );
// Int32 pKeyMod29 = intMath.getMod24( pubKey, 29 );


Int64 howMany = 0;

Int64 bigBase = 2 * 3 * 5 * 7 * 11 * 13 * 17;

const Int32 last17 = smallAr17.getLastAppend();

for( Int32 countBase = 0; countBase < 19 * 23; countBase++ )
  {
  Int64 basePart = bigBase * countBase;

  for( Int32 count = 0; count < last17; count++ )
    {
    Int64 allParts = basePart + smallAr17.getVal( count );

    if( !isGoodX( allParts, pKeyMod19, 19, 7 ))
      continue;

    if( !isGoodX( allParts, pKeyMod23, 23, 8 ))
      continue;

    // if( !isGoodX( allParts, pKeyMod29, 29, 9 ))
      // continue;

    howMany++;
    bigAr23.appendVal( allParts );
    }
  }

mainIO.appendChars( "howMany for 23 is: " );
Str showTest( howMany );
mainIO.appendStr( showTest );
mainIO.appendChars( "\n" );
}



/*
Change QuadRes.init() to show the first N primes.
2
3
5
7
11
13
17
19
23
29
31
37
41
43
47
53
59
61
67
71
73
79
83
89
97
101
103
107
109
113
127
131
137
139
149
151
157
163
167
173
179
181
191
193
197
199
211
223
227
229
233
239
241
251
257
263
269
271
277
281
283
293
307
311
313
317
331
337
347
349
353
359
367
373
379
383
389
397
401
409
419
421
431
433
439
443
449
457
461
463
467
479
487
491
499
503
509
521
523
541
*/



bool FindFacQr::findQr29( const Integer& pubKey,
                          Integer& prime1,
                          Integer& prime2,
                          IntegerMath& intMath,
                          FileIO& mainIO )
{
mainIO.appendChars( "Top of findQr29\n" );

// const Int64 max = 2L * 3L * 5L * 7L * 11L * 13L *
//                   17L * 19L * 23L * 29L;

// Max 29 is: 6,469,693,230

// mainIO.appendChars( "Max 29 is: " );
// Str showMax( max );
// mainIO.appendStr( showMax );

mainIO.appendChars( "\n" );


Int64 howMany = 0;

Int32 prodByte = pubKey.getD( 0 ) & 0xFF;

Int32 pKeyMod29 = intMath.getMod24( pubKey, 29 );
Int32 pKeyMod31 = intMath.getMod24( pubKey, 31 );
Int32 pKeyMod37 = intMath.getMod24( pubKey, 37 );
Int32 pKeyMod41 = intMath.getMod24( pubKey, 41 );
Int32 pKeyMod43 = intMath.getMod24( pubKey, 43 );

Int64 base = 2L * 3L * 5L * 7L * 11L * 13L * 17L
                                        * 19L * 23L;

Integer bigBase;
bigBase.setFromLong48( base );

Integer basePart;
Integer bigParts;

const Int32 last23 = bigAr23.getLastAppend();

for( Int32 countBase = 0; countBase < 100000; countBase++ )
  {
  basePart.copy( bigBase );
  intMath.multiplyInt( basePart, countBase );

  Int32 basePartByte = basePart.getD( 0 ) & 0xFF;
  Int32 basePart29 = intMath.getMod24( basePart, 29 );
  Int32 basePart31 = intMath.getMod24( basePart, 31 );
  Int32 basePart37 = intMath.getMod24( basePart, 37 );
  Int32 basePart41 = intMath.getMod24( basePart, 41 );
  Int32 basePart43 = intMath.getMod24( basePart, 43 );

  Int32 startAt = 0;
  if( countBase == 0 )
    startAt = 1; // Skip the number 1.

  for( Int32 count = startAt; count < last23; count++ )
    {
    const Int64 val23 = bigAr23.getVal( count );

    Int32 allBytes = basePartByte + (val23 & 0xFF);
    allBytes = allBytes * allBytes;
    allBytes += prodByte;
    allBytes = allBytes & 0xFF;
    if( !QuadRes::bytesQR( allBytes ))
      {
      // howMany++;
      continue;
      }

    Int64 allParts = basePart29 + val23;
    allParts = allParts % 29;
    if( !isGoodX( allParts, pKeyMod29, 29, 9 ))
      {
      // howMany++;
      continue;
      }

    allParts = basePart31 + val23;
    allParts = allParts % 31;
    if( !isGoodX( allParts, pKeyMod31, 31, 10 ))
      {
      // howMany++;
      continue;
      }

    allParts = basePart37 + val23;
    allParts = allParts % 37;
    if( !isGoodX( allParts, pKeyMod37, 37, 11 ))
      {
      // howMany++;
      continue;
      }

    allParts = basePart41 + val23;
    allParts = allParts % 41;
    if( !isGoodX( allParts, pKeyMod41, 41, 12 ))
      {
      // howMany++;
      continue;
      }

    allParts = basePart43 + val23;
    allParts = allParts % 43;
    if( !isGoodX( allParts, pKeyMod43, 43, 13 ))
      {
      // howMany++;
      continue;
      }

    howMany++;
    if( howMany > 1000000000 )
      throw "howMany it too big.";
      // return false;

    // mainIO.appendChars( "\nHowmany sqrRoot:\n" );
    // Do the big sqrRoot.
    bigParts.copy( basePart );
    bigParts.addLong48( bigAr23.getVal( count ));

    if( testSquare( pubKey,
                    bigParts,
                    prime1,
                    prime2,
                    intMath ))
      return true;

    }
  }

mainIO.appendChars( "\nWent past loops in findQr29.\n" );
return false;
}





bool FindFacQr::testSquare( const Integer& pubKey,
                            const Integer& x,
                            Integer& prime1,
                            Integer& prime2,
                            IntegerMath& intMath )
                            // FileIO& mainIO )

{
Integer test;
test.copy( x );
intMath.square( test );
test.add( pubKey );

Integer y;
if( !intMath.squareRoot( test, y ))
  return false;

prime1.copy( y );
intMath.subtract( prime1, x );

prime2.copy( y );
prime2.add( x );
return true;
}
