// Copyright Eric Chauvin, 2021.


#pragma once



#include "BasicTypes.h"
#include "Crt.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "IntBuf.h"
#include "SPrimes.h"



class CrtMath
  {
  private:
  Int32 testForCopy = 123;
  IntBuf* baseAr;

  void setupBaseArray( IntegerMath& intMath,
                       SPrimes& sPrimes );

  public:
  CrtMath( void );
  CrtMath( const CrtMath& in );
  ~CrtMath( void );
  void init( IntegerMath& intMath,
                             SPrimes& sPrimes );
  // void getInteger( Integer& accumulate,
  //                 Crt& input,
  //                 SPrimes& sPrimes );


  };
