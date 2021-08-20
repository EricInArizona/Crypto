// Copyright Eric Chauvin 2021.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Division
  {
  private:

  public:
  static bool shortDivide(
            const Integer& toDivideOriginal,
            const Integer& divideByOriginal,
            Integer& quotient,
            Integer& remainder );

  static Uint64 shortDivideRem(
                const Integer& toDivideOriginal,
                const Uint64 divideByU,
                Integer& quotient );

  static void divide(
                const Integer& toDivideOriginal,
                const Integer& divideByOriginal,
                Integer& quotient,
                Integer& remainder,
                IntegerMath& intMath );

  static bool longDivide1(
                    const Integer& toDivide,
                    const Integer& divideBy,
                    Integer& quotient,
                    Integer& remainder,
                    IntegerMath& intMath );

  static void testDivideBits(
                      const Uint64 maxValue,
                      const bool isTop,
                      const Uint32 testIndex,
                      const Integer& toDivide,
                      const Integer& divideBy,
                      Integer& quotient,
                       // Integer& remainder,
                       IntegerMath& intMath );

  static bool longDivide2(
                      const Integer& toDivide,
                      const Integer& divideBy,
                      Integer& quotient,
                      Integer& remainder,
                      IntegerMath& intMath );

  static Uint32 findShiftBy( Uint64 toTest );

  static void longDivide3(
                      const Integer& toDivide,
                      const Integer& divideBy,
                      Integer& quotient,
                      Integer& remainder,
                      IntegerMath& intMath );

  };
