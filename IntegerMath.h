// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "SPrimes.h"
#include "Str.h"
#include "FileIO.h"
#include "TwoDInt64.h"



class IntegerMath
  {
  private:
  Int32 testForCopy = 123;
  // Signed digits for use in subtraction.
  Int64* signedD;
  // Scratch pad, just like you would do on paper.
  TwoDInt64 M;
  Int64* scratch;

  void setMultiplySign( Integer& result,
                        const Integer& toMul );

  void searchSqrtXPart( Int32 testIndex,
                        Integer& fromSqr,
                        Integer& sqrRoot );


  public:
  IntegerMath( void );
  IntegerMath( const IntegerMath& in );
  ~IntegerMath( void  );
  static Int64 findLSqrRoot( Int64 toMatch );
  Int64 isDivisibleBySmallPrime(
                           const Integer& toTest,
                           SPrimes& sPrimes );

  void subtractLong( Integer& result,
                     const Int64 toSub );
  void add( Integer& result,
                      const Integer& toAdd );
  void subtract( Integer& result,
                         const Integer& toSub );
  void subtractPositive( Integer& result,
                         const Integer& toSub );

  void multiplyInt( Integer& result,
                    const Int64 toMul );
  Int32 multiplyIntFromCopy( Integer& result,
                              Integer& from,
                         const Int64 toMul );
  void multiplyLong( Integer& result,
                      const Int64 toMul );
  void multiply( Integer& result,
                 const Integer& toMul );

/*
  void setFromStr( Integer& result, Str& in );
*/

  Str toString10( const Integer& from );
  void square( Integer& toSquare );
  Int64 getMod24( const Integer& in,
                  const Int64 divisor );
  Int64 getMod48( const Integer& in,
                  const Int64 divisor );
  static Int64 mod48FromTwoLongs( Int64 P1,
                                  Int64 P0,
                                  Int64 divisor );

  void multiplyTop( Integer& result,
                    const Integer& toMul );
  void multiplyTopOne( Integer& result,
                       const Integer& toMul );
  bool squareRoot( const Integer& fromSqr,
                            Integer& sqrRoot );
  void searchSqrtXPart( Int32 testIndex,
                        const Integer& fromSqr,
                        Integer& sqrRoot );

  };
