// Copyright Eric Chauvin 2021.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
// #include "Exponents.h"



class Fermat
  {
  private:

  public:

  static void makeAPrime( Integer& result,
                   Uint32 setToIndex,
                   SPrimes& sPrimes,
                   IntegerMath& intMath,
                   Mod& mod ); // ,
                   // Exponents& exp,
                   // FileIO& mainIO );

  static bool isPrime( Integer& toTest,
                SPrimes& sPrimes,
                IntegerMath& intMath,
                Mod& mod ); // ,
                // Exponents& exp,
                // FileIO& mainIO );

  static bool isPrimeForOneValue(
                      Integer& toTest,
                      Uint64 base,
                      IntegerMath& intMath,
                      Mod& mod ); // ,
                      // Exponents& exp,
                      // FileIO& mainIO );


  };
