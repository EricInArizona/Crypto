// Copyright Eric Chauvin 2022.




#pragma once



#include "../LinuxApi/BasicTypes.h"

#include "../CryptoBase/GoodX.h"
#include "CrtTreeL.h"
#include "../CryptoBase/SPrimes.h"
#include "Crt3.h"
#include "CrtMath.h"
#include "../CryptoBase/QuadRes.h"



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


  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32 prodByte = 0;
  Integer pubKeyN;
  Crt3 bigXCrt;


  void setupGoodXQuadRes( Crt3& prod,
                          GoodX& goodX,
                          const SPrimes& sPrimes,
                          const QuadRes& quadRes );

  bool isAnswerSlow( // const GoodX& goodX,
                    const SPrimes& sPrimes,
                    const CrtMath& crtMath,
                    const MultInv& multInv,
                    IntegerMath& intMath,
                    CrtTreeL& crtTree,
                    FileIO& mainIO );

  bool testTopRow( const Int32 where,
                   const SPrimes& sPrimes,
                   const MultInv& multInv,
                   Crt3& toCheck,
                   const CrtMath& crtMath,
                   IntegerMath& intMath,
                   CrtTreeL& crtTree,
                   const GoodX& goodX,
                   FileIO& mainIO );

  bool testBaseByte( Crt3& toCheck,
                     const Int32 accum,
                     const Int32 where,
                     const Int32 baseAccum,
                     const Int32 baseByte,
                     CrtTreeL& crtTree,
                     const Int32 prime,
                     const CrtMath& crtMath,
                     const MultInv& multInv );


/*

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
                       CrtTreeL& crtTree,
                       FileIO& mainIO );

  bool runIt( const GoodX& goodX,
              const SPrimes& sPrimes,
              const CrtMath& crtMath,
              const MultInv& multInv,
              IntegerMath& intMath,
              CrtTreeL& crtTree,
              FileIO& mainIO );


  };
