// Copyright Eric Chauvin 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


/*
Mult inverse is A * x = 1 + Base * y
So (A * x = 1 + Base * y) mod 3 is one x for
each y.
Given a particular A and a particular Base,
there is a particular set of x and y mod 3.

The mult inverse of A mod Base is X.

*/



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
