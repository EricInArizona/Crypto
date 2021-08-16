// Copyright Eric Chauvin 2021.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Euclid
  {
  private:

  public:
  static void greatestComDiv( Integer& X,
                       Integer& Y,
                       Integer& gcd,
                       IntegerMath& intMath );


  static bool multInverse( Integer& knownX,
                           Integer& modulus,
                           Integer& inverse,
                           IntegerMath& intMath );

  };
