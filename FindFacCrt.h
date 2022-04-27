// Copyright Eric Chauvin 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/FileIO.h"

// #include "ProjConst.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/Integer.h"
#include "../CryptoBase/IntegerMath.h"
#include "../CryptoBase/MultInv.h"
#include "CrtMath.h"
#include "../CryptoBase/GoodX.h"
#include "Crt3.h"
#include "../CryptoBase/QuadRes.h"
#include "CrtTreeL.h"



class FindFacCrt
  {
  private:
  Int32 testForCopy = 123;
  CrtTreeL crtTree;

  public:
  FindFacCrt( void );
  FindFacCrt( const FindFacCrt& in );
  ~FindFacCrt( void );

/*
  bool getSmallFactor(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
                 // GoodX& goodX,
                 FileIO& mainIO );

  bool getSmallFactor1(
                 const Integer& pubKeyN,
                 Integer& find1,
                 Integer& find2,
                 IntegerMath& intMath,
                 const SPrimes& sPrimes,
                 const MultInv& multInv,
                 const CrtMath& crtMath,
                 FileIO& mainIO );
*/


  bool getFactorsQR( const Integer& pubKeyN,
                      Integer& find1,
                      Integer& find2,
                      IntegerMath& intMath,
                      const SPrimes& sPrimes,
                      const CrtMath& crtMath,
                      GoodX& goodX,
                      QuadRes& quadRes,
                      const MultInv& multInv,
                      FileIO& mainIO );

  bool firstTestSqrRoot( const Integer& prod,
                    IntegerMath& intMath,
                    FileIO& mainIO );

  bool checkEasyOnes( const Integer& prod,
                      IntegerMath& intMath,
                      const SPrimes& sPrimes,
                      FileIO& mainIO );

  void showFoundFactors(
                      const Integer& pubKeyN,
                      const Integer& find1,
                      const Integer& find2,
                      const Integer& foundX,
                      IntegerMath& intMath,
                      FileIO& mainIO );

  bool hasFactors( const Crt3& testX,
                   const Integer& pubKeyN,
                  Integer& find1,
                  Integer& find2,
                  IntegerMath& intMath,
                  // const SPrimes& sPrimes,
                  const CrtMath& crtMath,
                  // GoodX& goodX,
                  // const MultInv& multInv,
                  FileIO& mainIO );

  };
