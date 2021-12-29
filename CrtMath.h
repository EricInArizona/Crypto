// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "IntBuf.h"
#include "SPrimes.h"



class CrtMath
  {
  private:
  Int32 testForCopy = 123;
  IntBuf* baseAr;
  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  void setupBaseArray( IntegerMath& intMath,
                       SPrimes& sPrimes );

  public:
  CrtMath( void );
  CrtMath( const CrtMath& in );
  ~CrtMath( void );
  void init( IntegerMath& intMath,
                             SPrimes& sPrimes );

  void copyFromIntBuf( Integer& copyTo,
                           Uint32 where ) const;

  };
