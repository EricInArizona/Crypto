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
  Int32 testForCopy = 123;
  Integer* baseAr;
  Integer currentBase;


  public:
  Mod( void );
  Mod( const Mod& in );
  ~Mod( void );
  void setupBaseArray( // FileIO& mainIO,
                       Integer& setBase,
                       IntegerMath& intMath );
  void makeExact( Integer& exact,
                         IntegerMath& intMath );

  Uint32 reduce( // FileIO& mainIO,
                           Integer& result,
                           Integer& toReduce,
                           IntegerMath& intMath );

  void toPower( FileIO& mainIO,
                        Integer& result,
                        Integer& exponent,
                        Integer& modulus,
                        bool setUpBase,
                        IntegerMath& intMath );

  };



#endif
