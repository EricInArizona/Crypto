// Copyright Eric Chauvin 2021.


// Exponents and Discrete Logarithms


#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "NumbSys.h"
#include "Mod.h"
#include "TwoDUint64.h"


class Exponents
  {
  private:
  Int32 testForCopy = 123;
  NumbSys numbSys;
  Mod mod;
  TwoDUint64 baseArray;

  public:
  Exponents( void );
  Exponents( const Exponents& in );
  void toPower( Integer& result,
                   const Integer& exponent,
                   const Integer& modulus,
                   IntegerMath& intMath );


  };
