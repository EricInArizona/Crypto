// Copyright Eric Chauvin, 2022.



#pragma once


// An optimized version of Fermat's method of factoring.



#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/FileIO.h"
#include "../LinuxApi/Int32Array.h"
#include "../LinuxApi/Int64Array.h"

#include "../CryptoBase/Integer.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/IntegerMath.h"
#include "../CryptoBase/QuadRes.h"
#include "MultInv.h"
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


  void makeSmallAr17( const Integer& pubKey,
                      IntegerMath& intMath,
                      FileIO& mainIO );

  void makeBigAr23( const Integer& pubKey,
                    IntegerMath& intMath,
                    FileIO& mainIO );

  void makeBigAr29( const Integer& pubKey,
                    IntegerMath& intMath,
                    FileIO& mainIO );

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
