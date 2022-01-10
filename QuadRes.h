// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "BoolArray.h"



class QuadRes
  {
  private:
  Int32 testForCopy = 123;

  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  BoolArray* bArrays;

  public:
  QuadRes( void );
  QuadRes( const QuadRes& in );
  ~QuadRes( void );
  void init( SPrimes& sPrimes );
  inline bool getVal( Uint32 primeAt,
                      Uint32 where )
    {
    return bArrays[primeAt].getVal( where );
    }


  static bool bytesQR( const Uint32 test );
  static bool isSmallQR( const Uint32 number );
  static bool isQR17( const Uint32 number );
  static bool isQR19( const Uint32 number );
  static bool isQR23( const Uint32 number );
  // static bool isQR29( const Uint32 number );


  };
