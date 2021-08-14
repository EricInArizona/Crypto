// Copyright Eric Chauvin 2021.



#ifndef ECEuclid_H
#define ECEuclid_H



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

  };


#endif
