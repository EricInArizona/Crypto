// Copyright Eric Chauvin, 2021.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "SPrimes.h"
#include "Str.h"
#include "FileIO.h"
#include "TwoDUint64.h"



class IntegerMath
  {
  private:
  Int32 testForCopy = 123;
  // Signed digits for use in subtraction.
  Int64* signedD;
  // Scratch pad, just like you would do on paper.
  TwoDUint64 M;
  Uint64* scratch;

  void setMultiplySign( Integer& result,
                        Integer& toMul );

  void searchSqrtXPart( Uint32 testIndex,
                        Integer& fromSqr,
                        Integer& sqrRoot );


  public:
  IntegerMath( void );
  IntegerMath( const IntegerMath& in );
  ~IntegerMath( void  );
  static Uint64 findULSqrRoot( Uint64 toMatch );
  Uint64 isDivisibleBySmallPrime(
                              Integer& toTest,
                              SPrimes& sPrimes );

  void subtractULong( Integer& result,
                                  Uint64 toSub );
  void add( Integer& result, Integer& toAdd );
  void subtract( Integer& result,
                               Integer& toSub );
  void subtractPositive( Integer& result,
                               Integer& toSub );

  void multiplyUInt( Integer& result,
                                Uint64 toMul );
  Uint32 multiplyUIntFromCopy( Integer& result,
                             Integer& from,
                             Uint64 toMul );
  void multiplyULong( Integer& result,
                           Uint64 toMul );
  void multiply( Integer& result,
                               Integer& toMul );

/*
  void setFromStr( Integer& result, Str& in );
*/

  Str toString10( Integer& from );
  void square( Integer& toSquare );
  Uint64 getMod32( Integer& in, Uint64 divisor );
  Uint64 getMod64( Integer& in, Uint64 divisor );
  static Uint64 mod64FromTwoULongs( Uint64 P1,
                                 Uint64 P0,
                                 Uint64 divisor );
  void multiplyTop( Integer& result,
                               Integer& toMul );
  void multiplyTopOne( Integer& result,
                               Integer& toMul );

/*
  bool squareRoot( Integer& fromSqr,
                            Integer& sqrRoot );
*/


  };
