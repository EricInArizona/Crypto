// Copyright Eric Chauvin 2021.



#pragma once

// Modular Arithmetic.

//  Make mod.cpp like it is in the
//  Java code for Elliptic curve stuff.



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

  Uint32 reduce( // FileIO& mainIO,
                           Integer& result,
                           Integer& toReduce,
                           Integer& modulus,
                           IntegerMath& intMath );

  void toPower( FileIO& mainIO,
                        Integer& result,
                        Integer& exponent,
                        Integer& modulus,
                        IntegerMath& intMath );

  };
