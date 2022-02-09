// Copyright Eric Chauvin 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
#include "IntBuf.h"



class Exponents
  {
  private:
  Int32 testForCopy = 123;
  static const Int32 last =
                     ProjConst::exponentsLast;
  Mod mod;
  IntBuf* intBufAr;
  Integer currentBase;
  Integer currentModulus;

  public:
  Exponents( void );
  Exponents( const Exponents& in );
  ~Exponents( void );
  void setupBases( const Integer& base,
                   const Integer& modulus,
                   IntegerMath& intMath ); // ,
                   // FileIO& mainIO );
  void toPower( Integer& result,
                const Integer& exponent,
                const Integer& modulus,
                IntegerMath& intMath ); // ,
                // FileIO& mainIO );

  };
