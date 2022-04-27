// Copyright Eric Chauvin, 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once


// An optimized version of Fermat's method
// of factoring.



#include "../CppBase/BasicTypes.h"
#include "../CppBase/FileIO.h"
#include "../CppBase/Int32Array.h"
#include "../CppBase/Int64Array.h"

#include "../CryptoBase/Integer.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/IntegerMath.h"
#include "../CryptoBase/QuadRes.h"
#include "../CryptoBase/MultInv.h"
#include "../CryptoBase/GoodX.h"
#include "CrtMath.h"



class FindFacQr
  {
  private:
  Int32 testForCopy = 123;
  Int32Array smallAr17;
  Int32Array bigAr23;
  Int64Array bigAr29;
  QuadRes quadRes;
  MultInv multInv;
  CrtMath crtMath;
  Int32Array qrCounts;
  GoodX goodX;

  public:
  FindFacQr( void );
  FindFacQr( const FindFacQr& in );
  ~FindFacQr( void );


  inline bool testTopByte( const Int32 basePartByte,
                           const Int64 val23,
                           const Int32 prodByte )
    {
    Int32 allBytes = basePartByte + (val23 & 0xFF);
    allBytes = allBytes * allBytes;
    allBytes += prodByte;
    // allBytes = allBytes & 0xFF;
    return QuadRes::bytesQR( allBytes );
    }

  void setupGoodXQuadRes( const Integer& pubKey,
                          IntegerMath& intMath,
                          const SPrimes& sPrimes );

/*
  inline bool isGoodX( const Int64 x,
                       const Int32 pKeyMod,
                       const Int32 prime,
                       const Int32 primeAt )
    {
    Int64 test = x % prime;
    test = test * test;
    test += pKeyMod;
    test = test % prime;

    // return quadRes.getVal( primeAt, Casting::i64ToI32( test ));
    //                                   0x 0FFF FFFF
    return quadRes.getVal( primeAt, test & 0x0FFFFFFF );
    }
*/


  void makeSmallAr17( FileIO& mainIO );

  void makeBigAr23( FileIO& mainIO );

  void makeBigAr29( FileIO& mainIO );

  bool findIt( const Integer& pubKey,
               Integer& prime1,
               Integer& prime2,
               IntegerMath& intMath,
               SPrimes& sPrimes,
               FileIO& mainIO );

  bool findQr31( const Integer& pubKey,
                 Integer& prime1,
                 Integer& prime2,
                 IntegerMath& intMath,
                 FileIO& mainIO );

  bool testSquare( const Integer& pubKey,
                   const Integer& x,
                   Integer& prime1,
                   Integer& prime2,
                   IntegerMath& intMath );

  void makeQrCounts( const Integer& pubKey,
                     IntegerMath& intMath,
                     const SPrimes& sPrimes,
                     FileIO& mainIO );


  };
