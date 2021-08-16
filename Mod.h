// Copyright Eric Chauvin 2021.



#pragma once

// Modular Arithmetic.



#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"


class Mod
  {
  private:
  Int32 testForCopy = 123;
  // Integer* baseAr;
  // Use TwoDUint64  1,000 times 1,000 is
  // This is 8 bytes times digitArraySize *
  // digitArraySize, which is like 8 million bytes
  // or 32 million bytes or something like that.

  Integer currentBase;


  public:
  Mod( void );
  Mod( const Mod& in );
  ~Mod( void );
  void setupBaseArray( // FileIO& mainIO,
                       Integer& setBase // ,
                       // IntegerMath& intMath
                       );
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
