// Copyright Eric Chauvin 2021.



#pragma once


// Modular Arithmetic.


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "NumbSys.h"


class Mod
  {
  private:
  Int32 testForCopy = 123;
  NumbSys numbSys;

  public:
  Mod( void );
  Mod( const Mod& in );

  void makeExact( Integer& exact,
                  Integer& modulus,
                  IntegerMath& intMath );

  void toPower( Integer& result,
                Integer& exponent,
                Integer& modulus,
                IntegerMath& intMath );

  void verifyInBaseRange( Integer& toCheck,
                          Integer& modulus );

  void verifyMoreThanZero( Integer& toCheck );

  void add( Integer& result, Integer& toAdd,
            Integer& modulus,
            IntegerMath& intMath );

  void negate( Integer& result,
               Integer& modulus,
               IntegerMath& intMath );

  void subtract( Integer& result,
                 Integer& toSub,
                 Integer& modulus,
                 IntegerMath& intMath );

  void multiply( Integer& result,
                    Integer& toMul,
                    Integer& modulus,
                    IntegerMath& intMath );

  void square( Integer& result,
               Integer& modulus,
               IntegerMath& intMath );

  void divide( Integer& result,
                  Integer& numerator,
                  Integer& divisor,
                  Integer& modulus,
                  IntegerMath& intMath );

  };
