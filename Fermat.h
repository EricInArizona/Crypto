// Copyright Eric Chauvin 2021.



#ifndef ECFermat_H
#define ECFermat_H



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"



class Fermat
  {
  private:
  Mod mod;
  Uint32 forCopyTest = 123;
  public:
  Fermat( void );
  Fermat( const Fermat& in );

  bool makeAPrime( FileIO& mainIO,
                   Integer& result,
                   Uint32 setToIndex,
                   // Uint32 howMany,
                   SPrimes& sPrimes,
                   IntegerMath& intMath );

  bool isPrime( FileIO& mainIO,
                Integer& toTest,
                // Uint32 howMany,
                SPrimes& sPrimes,
                IntegerMath& intMath );

  bool isPrimeForOneValue( FileIO& mainIO,
                      Integer& toTest,
                      Uint64 base,
                      IntegerMath& intMath );


  };


#endif
