// Copyright Eric Chauvin, 2022.



#pragma once


// Find small factors.


#include "..\LinuxApi\BasicTypes.h"
#include "..\LinuxApi\FileIO.h"
#include "..\LinuxApi\Int32Array.h"
#include "..\CryptoBase\Integer.h"
#include "..\CryptoBase\SPrimes.h"
#include "..\CryptoBase\IntegerMath.h"




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
