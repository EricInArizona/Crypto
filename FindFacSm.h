// Copyright Eric Chauvin, 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


// Find small factors.


#include "../CppBase/BasicTypes.h"
#include "../CppBase/FileIO.h"
#include "../CppBase/Int32Array.h"
#include "../CryptoBase/Integer.h"
#include "../CryptoBase/SPrimes.h"
#include "../CryptoBase/IntegerMath.h"




class FindFacSm
  {
  private:
  Int32 testForCopy = 123;
  Int32Array smallAr13;
  Int32Array bigAr19;

  public:
  FindFacSm( void );
  FindFacSm( const FindFacSm& in );
  ~FindFacSm( void );
  void makeSmallAr13( void ); // FileIO& mainIO );
  void makeBigAr19( void ); // FileIO& mainIO );

  Int64 findIt( const Integer& pubKey,
                const Int64 maxBase,
                IntegerMath& intMath,
                const SPrimes& sPrimes,
                FileIO& mainIO );

  Int64 findSmall31( const Integer& pubKey,
                     const Int64 maxBase,
                     IntegerMath& intMath,
                     FileIO& mainIO );


  };
