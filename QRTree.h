// Copyright Eric Chauvin 2022.




#pragma once



#include "../LinuxApi/BasicTypes.h"

#include "GoodX.h"
#include "CrtTreeL.h"
#include "SPrimes.h"
#include "Crt3.h"
#include "CrtMath.h"
#include "QuadRes.h"



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



class QRTree
  {
  private:
  Int32 testForCopy = 123;

  CrtTreeL crtTreeL;

  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32 prodByte = 0;
  Integer pubKeyN;
  Crt3 bigXCrt;


/*
  inline Int32 getAccum( const Int32 row,
                   const Int32 col,
                   const Int32 prime,
                   const CrtMath& crtMath ) const
    {
    // Calling it with count - 1 when count
    // is zero.
    RangeC::test2( row, 0, last - 1,
              "getAccum  where range." );

    Int32 top = row;
    if( top > index )
      top = index;

    // The crtDigit is all ones at index 0.
    // So it would be this times 1.
    // This is either one or zero.
    Int32 result = nodesAr[0].digit;
    if( row == 0 )
      return result;

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
*/


/*
  inline Int32 getAccumByte( const Int32 row,
                 const CrtMath& crtMath ) const

    {
    if( row < 0 )
      return 0;

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
    Int32 testBits = getAccumByte( index,
                                   crtMath );
    // nodesAr[index].getAccumByte();

    testBits = testBits * testBits;
    testBits += prodByte;
    testBits = testBits & 0xFF;

    // 44 out of 256 possible bytes are true.
    if( QuadRes::bytesQR( testBits ))
      return true;

    return false;
    }
*/


  void setupGoodXQuadRes( Crt3& prod,
                          GoodX& goodX,
                          const SPrimes& sPrimes,
                          const QuadRes& quadRes );

  bool isAnswerSlow( // const GoodX& goodX,
                    const SPrimes& sPrimes,
                    const CrtMath& crtMath,
                    const MultInv& multInv,
                    IntegerMath& intMath,
                    FileIO& mainIO );

  // bool testBaseByte( const Int32 where,
     //                const Int32 baseAccum,
     //                const Int32 baseByte );

  bool testTopRow( const Int32 where,
                   const SPrimes& sPrimes,
                   const MultInv& multInv,
                   Crt3& toCheck,
                   const CrtMath& crtMath,
                   IntegerMath& intMath,
                   FileIO& mainIO );



/*
  bool isGoodXAt( const Int32 where,
               const GoodX& goodX,
               const CrtMath& crtMath,
               const SPrimes& sPrimes ) const;

  bool isFullGoodX2( const GoodX& goodX,
                const CrtMath& crtMath,
                const SPrimes& sPrimes ) const;

  void getBiggestX( Integer& bigX,
                    IntegerMath& intMath,
                    const SPrimes& sPrimes,
                    const MultInv& multInv,
                    const CrtMath& crtMath,
                    FileIO& mainIO );
*/

  public:
  QRTree( void );
  QRTree( const QRTree& in );
  ~QRTree( void );

  void setStartValues( const Integer& setpubKeyN,
                       GoodX& goodX,
                       QuadRes& quadRes,
                       const CrtMath& crtMath,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes,
                       const MultInv& multInv,
                       FileIO& mainIO );

  bool runIt( // const GoodX& goodX,
              const SPrimes& sPrimes,
              const CrtMath& crtMath,
              const MultInv& multInv,
              IntegerMath& intMath,
              FileIO& mainIO );

  void setFromCrtTree( Crt3& toSet,
                   const CrtMath& crtMath,
                   const SPrimes& sPrimes,
                   const MultInv& multInv );

  };
