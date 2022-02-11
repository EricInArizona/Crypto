// Copyright Eric Chauvin 2022.



#pragma once



#include "BasicTypes.h"
#include "QRTreeNode.h"
#include "GoodX.h"
#include "SPrimes.h"
#include "Crt2.h"
#include "CrtMath.h"
#include "QuadRes.h"


class QRTree
  {
  private:
  Int32 testForCopy = 123;

  QRTreeNode* nodesAr;
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32 length = 0;
  Int32 prodByte = 0;
  Integer pubKeyN;
  Crt2 bigXCrt2;

  inline Int32 getAccum( const Int32 row,
                   const Int32 col,
                   const Int32 prime,
                   const CrtMath& crtMath ) const
    {
    Int32 top = row;
    if( top > length )
      top = length;

    // The crtDigit is all ones at index 0.
    // So it would be this times 1.
    // This is either one or zero.
    Int32 result = nodesAr[0].digit;

    for( Int32 count = 1; count <= top; count++ )
      {
      Int32 accum = crtMath.getCrtDigit(
                                   count, col );

      accum = accum * nodesAr[count].digit;
      result += accum;
      result = result % prime;
      }

    return result;
    }

  inline Int32 getAccumByte( const Int32 row,
                 const CrtMath& crtMath ) const

    {
    // It is either zero or one.
    Int32 result = nodesAr[0].digit;

    for( Int32 count = 1; count <= row; count++ )
      {
      Int32 accumB = crtMath.getBaseByte( count );
      accumB = accumB * nodesAr[count].digit;
      result += accumB;
      result = result & 0xFF;
      }

    return result;
    }

  inline bool isGoodTopAccumByte(
                     const CrtMath& crtMath )
    {
    Int32 testBits = getAccumByte( length,
                                   crtMath );
    // nodesAr[length].getAccumByte();

    testBits = testBits * testBits;
    testBits += prodByte;
    testBits = testBits & 0xFF;

    // 44 out of 256 possible bytes are true.
    if( QuadRes::bytesQR( testBits ))
      return true;

    return false;
    }


  void setupGoodXQuadRes( Crt& prod,
                       GoodX& goodX,
                       const SPrimes& sPrimes,
                       const QuadRes& quadRes );

  bool isTheAnswer( const GoodX& goodX,
                    const SPrimes& sPrimes,
                    const CrtMath& crtMath,
                    IntegerMath& intMath );

  void setAllZeros( const Int32 start );

/*
  void setFirstGoodXUpTo(
                   const Int32 start,
                   const Int32 end,
                   const SPrimes& sPrimes,
                   const GoodX& goodX,
                   const CrtMath& crtMath );
*/

  void setFirstGoodXAt( const Int32 where,
                 const SPrimes& sPrimes,
                 const GoodX& goodX,
                 const CrtMath& crtMath );

  void setFirstGoodXDepth(
                      Int32 depth,
                      const SPrimes& sPrimes,
                      const GoodX& goodX,
                      const CrtMath& crtMath );

  bool setNextGoodXAt( const Int32 where,
                 const SPrimes& sPrimes,
                 const GoodX& goodX,
                 const CrtMath& crtMath );

  bool testTopRowGoodX( const Int32 where,
                     const SPrimes& sPrimes,
                     const GoodX& goodX,
                     const CrtMath& crtMath,
                     IntegerMath& intMath );

  bool isFullGoodX( const GoodX& goodX,
                const CrtMath& crtMath,
                const SPrimes& sPrimes ) const;

  void getBiggestX( Integer& bigX,
                    IntegerMath& intMath,
                    const SPrimes& sPrimes,
                    const MultInv& multInv,
                    const CrtMath& crtMath,
                    FileIO& mainIO );

  public:
  QRTree( void );
  QRTree( const QRTree& in );
  ~QRTree( void );

  void setStartValues(
                   const Integer& setpubKeyN,
                   GoodX& goodX,
                   QuadRes& quadRes,
                   const CrtMath& crtMath,
                   IntegerMath& intMath,
                   const SPrimes& sPrimes,
                   const MultInv& multInv,
                   FileIO& mainIO );

  bool runIt( const GoodX& goodX,
              const SPrimes& sPrimes,
              const CrtMath& crtMath,
              IntegerMath& intMath,
              FileIO& mainIO );

  void setCrt2( Crt2& toSet );

  };
