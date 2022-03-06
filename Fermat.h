// Copyright Eric Chauvin 2021 - 2022.



#pragma once



#include "../LinuxApi/BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"



class Fermat
  {
  private:

  public:

  static void makeAPrime( Integer& result,
                   const Int32 setToIndex,
                   const SPrimes& sPrimes,
                   IntegerMath& intMath,
                   Mod& mod );
                   // FileIO& mainIO );

  static bool isPrime( const Integer& toTest,
                const SPrimes& sPrimes,
                IntegerMath& intMath,
                Mod& mod );
                // FileIO& mainIO );

  static bool isPrimeForOneValue(
                      const Integer& toTest,
                      const Int64 base,
                      IntegerMath& intMath,
                      Mod& mod );
                      // FileIO& mainIO );


  };
