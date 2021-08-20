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
                        const Integer& toMul );

  void searchSqrtXPart( Uint32 testIndex,
                        Integer& fromSqr,
                        Integer& sqrRoot );


  public:
  IntegerMath( void );
  IntegerMath( const IntegerMath& in );
  ~IntegerMath( void  );
  static Uint64 findULSqrRoot( Uint64 toMatch );
  Uint64 isDivisibleBySmallPrime(
                           const Integer& toTest,
                           SPrimes& sPrimes );

  void subtractULong( Integer& result,
                      const Uint64 toSub );
  void add( Integer& result,
                      const Integer& toAdd );
  void subtract( Integer& result,
                         const Integer& toSub );
  void subtractPositive( Integer& result,
                         const Integer& toSub );

  void multiplyUInt( Integer& result,
                     const Uint64 toMul );
  Uint32 multiplyUIntFromCopy( Integer& result,
                             Integer& from,
                       const Uint64 toMul );
  void multiplyULong( Integer& result,
                      const Uint64 toMul );
  void multiply( Integer& result,
                 const Integer& toMul );

/*
  void setFromStr( Integer& result, Str& in );
*/

  Str toString10( const Integer& from );
  void square( Integer& toSquare );
  Uint64 getMod32( const Integer& in,
                        const Uint64 divisor );
  Uint64 getMod64( const Integer& in,
                        const Uint64 divisor );
  static Uint64 mod64FromTwoULongs( Uint64 P1,
                                 Uint64 P0,
                                 Uint64 divisor );
  void multiplyTop( Integer& result,
                    const Integer& toMul );
  void multiplyTopOne( Integer& result,
                       const Integer& toMul );

/*
  bool squareRoot( Integer& fromSqr,
                            Integer& sqrRoot );
*/


  };
