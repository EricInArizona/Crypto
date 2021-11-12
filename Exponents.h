// Copyright Eric Chauvin 2021.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "NumbSys.h"
#include "Mod.h"
#include "IntBuf.h"


// The size of this is the number of bits
// times the size of an IntBuf.  An IntBuf takes
// up about ProjConst::digitArraySize
// time 4 bytes, or about 2,000 bytes each.
// So something like 2,000 times 1,000 bytes.


class Exponents
  {
  private:
  Int32 testForCopy = 123;
  static const Uint32 last = 1000;
  NumbSys numbSys;
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
                IntegerMath& intMath,
                FileIO& mainIO );

  };
