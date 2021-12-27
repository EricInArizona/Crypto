// Copyright Eric Chauvin, 2021.



#pragma once


#include "BasicTypes.h"
#include "Crt.h"
#include "Crt2.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "IntBuf.h"
#include "SPrimes.h"



class CrtMath
  {
  private:
  Int32 testForCopy = 123;
  IntBuf* baseAr;
  Crt* baseArCrt;
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

  void crt2ToInteger( const Crt2& from,
                      Integer& toSet,
                      IntegerMath& intMath );

  void crtToCrt2( const Crt& from, Crt2& toSet,
                  Integer& accum,
                  SPrimes& sPrimes,
                  IntegerMath& intMath );

  void crtToCrt2V1( const Crt& from, Crt2& toSet,
                    Integer& accum,
                    SPrimes& sPrimes,
                    IntegerMath& intMath );

  void crtToCrt2V2( const Crt& from, Crt2& toSet,
                    Integer& accum,
                    SPrimes& sPrimes,
                    IntegerMath& intMath );

  bool test( Integer& t1, IntegerMath& intMath,
                          SPrimes& sPrimes );



  };
