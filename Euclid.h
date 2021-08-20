// Copyright Eric Chauvin 2021.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Euclid
  {
  private:

  public:
  static void greatestComDiv(
                       const Integer& X,
                       const Integer& Y,
                       Integer& gcd,
                       IntegerMath& intMath );


  static bool multInverse(
                       const Integer& knownX,
                       const Integer& modulus,
                       Integer& inverse,
                       IntegerMath& intMath );

  };
