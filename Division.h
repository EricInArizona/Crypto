// Copyright Eric Chauvin 2021.



#ifndef ECDivision_H
#define ECDivision_H



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Division
  {
  private:

  public:
  static bool shortDivide( Integer& toDivide,
                    Integer& divideBy,
                    Integer& quotient,
                    Integer& remainder );

  static Uint64 shortDivideRem(
                    Integer& toDivideOriginal,
                    Uint64 divideByU,
                    Integer& quotient );

  static void divide( Integer& toDivideOriginal,
                    Integer& divideByOriginal,
                    Integer& quotient,
                    Integer& remainder,
                    IntegerMath& intMath );

  static bool longDivide1( Integer& toDivide,
                    Integer& divideBy,
                    Integer& quotient,
                    Integer& remainder,
                    IntegerMath& intMath );

  static void testDivideBits( Uint64 maxValue,
                       bool isTop,
                       Uint32 testIndex,
                       Integer& toDivide,
                       Integer& divideBy,
                       Integer& quotient,
                       Integer& remainder,
                       IntegerMath& intMath );

  static bool longDivide2( Integer& toDivide,
                         Integer& divideBy,
                         Integer& quotient,
                         Integer& remainder,
                         IntegerMath& intMath );

  static Int32 findShiftBy( Uint64 toTest );

  static void longDivide3( Integer& toDivide,
                         Integer& divideBy,
                         Integer& quotient,
                         Integer& remainder,
                         IntegerMath& intMath );

  };


#endif
