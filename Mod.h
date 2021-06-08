// Copyright Eric Chauvin 2021.



// Modular Arithmetic.


#ifndef ECMod_H
#define ECMod_H



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Mod
  {
  private:
  Integer baseAr[Integer::digitArraySize] = {};
  Integer currentBase;


  public:
  Mod( void );
  Mod( const Mod& in );
  // ~Mod( void );
  void setupBaseArray( Integer& setBase,
                         IntegerMath& intMath );
  void makeExact( Integer& exact,
                         IntegerMath& intMath );

  Uint32 reduce( Integer& result,
                           Integer& toReduce,
                           IntegerMath& intMath );

  void toPower( Integer& result,
                        Integer& exponent,
                        Integer& modulus,
                        bool setUpBase,
                        IntegerMath& intMath );

  };



#endif
