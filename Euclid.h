// Copyright Eric Chauvin 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


// Mult inverse is A * x = 1 + Base * y



class Euclid
  {
  private:

  public:
  static Int64 GcdL1( const Int64 x,
                      const Int64 y );

  static void greatestComDiv(
                       const Integer& X,
                       const Integer& Y,
                       Integer& gcd,
                       IntegerMath& intMath );

  static Int64 multInvL( const Int64 knownX,
                         const Int64 modulus );

  static bool multInverse(
                       const Integer& knownX,
                       const Integer& modulus,
                       Integer& inverse,
                       IntegerMath& intMath );

  };
