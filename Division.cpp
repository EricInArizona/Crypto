// Copyright Eric Chauvin 2021.


// To do:
// Make some better division algorithms.


#include "Division.h"


/*
bool Division::shortDivide( Integer& toDivide,
                            Integer& divideBy,
                            Integer& quotient,
                            Integer& remainder )
{
quotient.copy( toDivide );
// DivideBy has an Index of zero:
Uint64 divideByU = divideBy.getD( 0 );
Uint64 remainderU = 0;

// Get the first one set up.
if( divideByU > quotient.getD( quotient.
                                   getIndex()))
  {
  quotient.setD( quotient.getIndex(), 0 );
  }
else
  {
  Uint64 oneDigit = quotient.getD( quotient.
                                    getIndex() );
  quotient.setD( quotient.getIndex(), oneDigit /
                                     divideByU );
  remainderU = oneDigit % divideByU;
  toDivide.setD( toDivide.getIndex(), remainderU );
  }

// Now do the rest.
for( Int32 count = quotient.getIndex();
                           count >= 1; count-- )
  {
  Uint64 twoDigits = toDivide.getD( count );
  twoDigits <<= 32;
  twoDigits |= toDivide.getD( count - 1 );
  quotient.setD( count - 1, twoDigits /
                                    divideByU );
  remainderU = twoDigits % divideByU;
  toDivide.setD( count, 0 );
  toDivide.setD( count - 1, remainderU );
  }

// Set the index for the quotient.
// The quotient would have to be at least 1 here,
// so it will find where to set the index.
for( Int32 count = quotient.getIndex();
                           count >= 0; count-- )
  {
  if( quotient.getD( count ) != 0 )
    {
    quotient.setIndex( count );
    break;
    }
  }

remainder.setD( 0, remainderU );
remainder.setIndex( 0 );
if( remainderU == 0 )
  return true;
else
  return false;

}
*/



// This is a variation on ShortDivide that returns
// the remainder.
// Also, divideBy is a Uint64.
Uint64 Division::shortDivideRem(
                       Integer& toDivideOriginal,
                       Uint64 divideByU,
                       Integer& quotient )
{
if( toDivideOriginal.isULong())
  {
  Uint64 toDiv = toDivideOriginal.getAsULong();
  Uint64 q = toDiv / divideByU;
  quotient.setFromULong( q );
  return toDiv % divideByU;
  }

Integer toDivide;
toDivide.copy( toDivideOriginal );
quotient.copy( toDivide );
Uint64 remainderU = 0;
if( divideByU > quotient.getD( quotient.
                                    getIndex() ))
  {
  quotient.setD( quotient.getIndex(), 0 );
  }
else
  {
  Uint64 oneDigit = quotient.getD( quotient.
                                   getIndex() );
  quotient.setD( quotient.getIndex(), oneDigit /
                                     divideByU );
  remainderU = oneDigit % divideByU;
  toDivide.setD( toDivide.getIndex(), remainderU );
  }

for( Int32 count = quotient.getIndex();
                           count >= 1; count-- )
  {
  Uint64 twoDigits = toDivide.getD( count );
  twoDigits <<= 32;
  twoDigits |= toDivide.getD( count - 1 );
  quotient.setD( count - 1, twoDigits / divideByU );
  remainderU = twoDigits % divideByU;
  toDivide.setD( count, 0 );
  toDivide.setD( count - 1, remainderU );
  }

for( Int32 count = quotient.getIndex();
                            count >= 0; count-- )
  {
  if( quotient.getD( count ) != 0 )
    {
    quotient.setIndex( count );
    break;
    }
  }

return remainderU;
}





void Division::divide( Integer& toDivideOriginal,
                       Integer& divideByOriginal,
                       Integer& quotient,
                       Integer& remainder,
                       IntegerMath& intMath )
{
if( toDivideOriginal.getIsNegative() )
  throw "Divide() is negative.";

if( divideByOriginal.getIsNegative() )
  throw "Divide() is negative.";

if( divideByOriginal.isZero() )
  throw "Divide() dividing by zero.";

/*
Integer toDivide;
toDivide.copy( toDivideOriginal );

Integer divideBy;
divideBy.copy( divideByOriginal );

if( toDivide.paramIsGreater( divideBy ))
  {
  quotient.setToZero();
  remainder.copy( toDivide );
  return;
  }

if( toDivide.isEqual( divideBy ))
  {
  quotient.setFromULong( 1 );
  remainder.setToZero();
  return;
  }

// At this point divideBy is smaller than toDivide.
if( toDivide.isULong() )
  {
  Uint64 toDivideU = toDivide.getAsULong();
  Uint64 divideByU = divideBy.getAsULong();
  Uint64 quotientU = toDivideU / divideByU;
  Uint64 remainderU = toDivideU % divideByU;
  quotient.setFromULong( quotientU );
  remainder.setFromULong( remainderU );
  return;
  }

if( divideBy.getIndex() == 0 )
  {
  shortDivide( toDivide, divideBy, quotient,
                                     remainder );
  return;
  }

Integer toDivideTest2;
Integer divideByTest2;
Integer quotientTest2;
Integer remainderTest2;
Integer toDivideTest3;
Integer divideByTest3;
Integer quotientTest3;
Integer remainderTest3;

toDivideTest2.copy( toDivide );
toDivideTest3.copy( toDivide );

divideByTest2.copy( divideBy );
divideByTest3.copy( divideBy );

longDivide1( toDivideTest2, divideByTest2,
                quotientTest2, remainderTest2,
                intMath );
longDivide2( toDivideTest3, divideByTest3,
                quotientTest3, remainderTest3,
                intMath );
longDivide3( toDivide, divideBy,
                quotient, remainder,
                intMath );

if( !quotient.isEqual( quotientTest2 ))
  throw "!quotient.isEqual( quotientTest2 )";

if( !quotient.isEqual( quotientTest3 ))
  throw "!quotient.isEqual( quotientTest3 )";

if( !remainder.isEqual( remainderTest2 ))
  throw "!remainder.isEqual( remainderTest2 )";

if( !remainder.isEqual( remainderTest3 ))
  throw "!remainder.isEqual( remainderTest3 )";
*/
}



/*
bool Division::longDivide1( Integer& toDivide,
                            Integer& divideBy,
                            Integer& quotient,
                            Integer& remainder,
                            IntegerMath& intMath )
{
Uint32 digit = 0;
Int32 testIndex = toDivide.getIndex() -
                             divideBy.getIndex();

Integer test1;

if( testIndex != 0 )
  {
  // Is 1 too high?
  test1.setDigitAndClear( testIndex, 1 );
  intMath.multiplyTopOne( test1, divideBy );
  if( toDivide.paramIsGreater( test1 ))
    testIndex--;

  }

quotient.setDigitAndClear( testIndex, 1 );
quotient.setD( testIndex, 0 );
Uint32 bitTest = 0x80000000;
while( true )
  {
  for( Int32 bitCount = 31; bitCount >= 0;
                                     bitCount-- )
    {
    test1.copy( quotient );
    digit = (Uint32)test1.getD( testIndex ) |
                                         bitTest;
    test1.setD( testIndex, digit );
    intMath.multiply( test1, divideBy );
    if( test1.paramIsGreaterOrEq( toDivide ))
      {
      digit = (Uint32)quotient.getD( testIndex )
                                        | bitTest;
      // I want to keep this bit because it
      // passed the test.
      quotient.setD( testIndex, digit );
      }

    bitTest >>= 1;
    }

  if( testIndex == 0 )
    break;

  testIndex--;
  bitTest = 0x80000000;
  }

test1.copy( quotient );
intMath.multiply( test1, divideBy );
if( test1.isEqual( toDivide ) )
  {
  remainder.setToZero();
  return true; // Divides exactly.
  }

remainder.copy( toDivide );
intMath.subtract( remainder, test1 );

// Does not divide it exactly.
return false;
}
*/



/*
void Division::testDivideBits( Uint64 maxValue,
                               bool isTop,
                               Uint32 testIndex,
                               Integer& toDivide,
                           Integer& divideBy,
                           Integer& quotient,
                           Integer& remainder,
                           IntegerMath& intMath )
{
// For a particular value of TestIndex, this does
// the for-loop to test each bit.

Integer testForBits;

Uint32 bitTest = 0x80000000;
for( Int32 bitCount = 31; bitCount >= 0;
                                    bitCount-- )
  {
  if( (quotient.getD( testIndex ) | bitTest) >
                                        maxValue )
    {
    // If it's more than the MaxValue then the
    // multiplication test can be skipped for
    // this bit.
    // SkippedMultiplies++;
    bitTest >>= 1;
    continue;
    }

  testForBits.copy( quotient );

  // Is it only doing the multiplication for the
  // top digit?
  if( isTop )
    {
    testForBits.setD( testIndex, testForBits.
                   getD( testIndex ) | bitTest );
    intMath.multiplyTop( testForBits, divideBy );
    }
  else
    {
    testForBits.setD( testIndex, testForBits.
                  getD( testIndex ) | bitTest );
    intMath.multiply( testForBits, divideBy );
    }

  if( testForBits.paramIsGreaterOrEq( toDivide ))
    {
    // It passed the test, so keep the bit.
    quotient.setD( testIndex, quotient.getD(
                       testIndex ) | bitTest );
    }

  bitTest >>= 1;
  }
}
*/



/*
// This works like LongDivide1 except that it
// estimates the maximum value for the digit and
// the for-loop for bit testing is called
// as a separate function.
bool Division::longDivide2( Integer& toDivide,
                            Integer& divideBy,
                            Integer& quotient,
                            Integer& remainder,
                            IntegerMath& intMath )
{
Integer test1;
Int32 testIndex = toDivide.getIndex() -
                             divideBy.getIndex();

if( testIndex != 0 )
  {
  // Is 1 too high?
  test1.setDigitAndClear( testIndex, 1 );
  intMath.multiplyTopOne( test1, divideBy );
  if( toDivide.paramIsGreater( test1 ))
    testIndex--;

  }

// If you were multiplying 99 times 97 you'd get
// 9,603 and the upper two digits [96] are used
// to find the MaxValue.  But if you multiply
// 12 * 13 you'd have 156 and only the upper one
// digit is used to find the MaxValue.
// Here it checks if it should use one digit or
// two:
Uint64 maxValue = 0;
if( (toDivide.getIndex() - 1) >
              (divideBy.getIndex() + testIndex) )
  {
  maxValue = toDivide.getD( toDivide.getIndex());
  }
else
  {
  maxValue = toDivide.getD( toDivide.getIndex() )
                                            << 32;
  maxValue |= toDivide.getD( toDivide.getIndex()
                                            - 1 );
  }

maxValue = maxValue / divideBy.getD(
                          divideBy.getIndex() );
quotient.setDigitAndClear( testIndex, 1 );
quotient.setD( testIndex, 0 );

testDivideBits( maxValue,
                    true,
                    testIndex,
                    toDivide,
                    divideBy,
                    quotient,
                    remainder,
                    intMath );

if( testIndex == 0 )
  {
  test1.copy( quotient );
  intMath.multiply( test1, divideBy );
  remainder.copy( toDivide );
  intMath.subtract( remainder, test1 );

  if( divideBy.paramIsGreater( remainder ))
    throw "Remainder > DivideBy LongDivide2().";

  if( remainder.isZero() )
    return true;
  else
    return false;

  }

testIndex--;
while( true )
  {
  // This remainder is used the same way you do
  // long division with paper and pen and you
  // keep working with a remainder until the
  // remainder is reduced to something smaller
  // than DivideBy.  You look at the remainder
  // to estimate your next quotient digit.

  test1.copy( quotient );
  intMath.multiply( test1, divideBy );
  remainder.copy( toDivide );
  intMath.subtract( remainder, test1 );
  maxValue = remainder.getD( remainder.
                              getIndex()) << 32;
  maxValue |= remainder.getD( remainder.
                                 getIndex() - 1 );
  maxValue = maxValue / divideBy.getD(
                           divideBy.getIndex());
  testDivideBits( maxValue,
                      false,
                      testIndex,
                      toDivide,
                      divideBy,
                      quotient,
                      remainder,
                      intMath );

  if( testIndex == 0 )
    break;

  testIndex--;
  }

test1.copy( quotient );
intMath.multiply( test1, divideBy );
remainder.copy( toDivide );
intMath.subtract( remainder, test1 );

if( divideBy.paramIsGreater( remainder ))
  throw "Remainder > DivideBy longDivide2().";

if( remainder.isZero() )
  return true;
else
  return false;

}
*/



/*
// If you multiply the numerator and the
// denominator by the same amount then the
// quotient is still the same.  By shifting
// left (multiplying by twos) the MaxValue
// upper limit is more accurate.
// This is called normalization.
Int32 Division::findShiftBy( Uint64 toTest )
{
Int32 shiftBy = 0;
// If it's not already shifted all the way over
// to the left, shift it all the way over.
for( Uint32 count = 0; count < 32; count++ )
  {
  if( (toTest & 0x80000000) != 0 )
    break;

  shiftBy++;
  toTest <<= 1;
  }

return shiftBy;
}
*/



/*
void Division::longDivide3( Integer& toDivide,
                            Integer& divideBy,
                            Integer& quotient,
                            Integer& remainder,
                            IntegerMath& intMath )
{
Integer test2;

Int32 testIndex = toDivide.getIndex() -
                           divideBy.getIndex();
if( testIndex < 0 )
  throw "TestIndex < 0 in Divide3.";

Integer testForDivide1;

if( testIndex != 0 )
  {
  // Is 1 too high?
  testForDivide1.setDigitAndClear( testIndex, 1 );
  intMath.multiplyTopOne( testForDivide1,
                                      divideBy );
  if( toDivide.paramIsGreater( testForDivide1 ))
    testIndex--;

  }

Integer toDivideKeep;
Integer divideByKeep;

// Keep a copy of the originals.
toDivideKeep.copy( toDivide );
divideByKeep.copy( divideBy );
Uint64 testBits = divideBy.getD( divideBy.
                                      getIndex());
Int32 shiftBy = findShiftBy( testBits );
toDivide.shiftLeft( shiftBy );
divideBy.shiftLeft( shiftBy );
Uint64 maxValue = 0;
if( (toDivide.getIndex() - 1) > (divideBy.
                      getIndex() + testIndex) )
  {
  maxValue = toDivide.getD( toDivide.getIndex());
  }
else
  {
  maxValue = toDivide.getD( toDivide.
                               getIndex()) << 32;
  maxValue |= toDivide.getD( toDivide.getIndex()
                                          - 1 );
  }

Uint64 denom = divideBy.getD( divideBy.getIndex());
if( denom != 0 )
  maxValue = maxValue / denom;
else
  maxValue = 0xFFFFFFFF;

if( maxValue > 0xFFFFFFFF )
  maxValue = 0xFFFFFFFF;

if( maxValue == 0 )
  throw "MaxValue zero at top in LongDivide3().";

quotient.setDigitAndClear( testIndex, 1 );
quotient.setD( testIndex, 0 );
testForDivide1.copy( quotient );
testForDivide1.setD( testIndex, maxValue );
intMath.multiplyTop( testForDivide1, divideBy );


// Test:
test2.copy( quotient );
test2.setD( testIndex, maxValue );
intMath.multiply( test2, divideBy );
if( !test2.isEqual( testForDivide1 ))
  throw "In Divide3() !IsEqual.";


if( testForDivide1.paramIsGreaterOrEq( toDivide ))
  {
  // ToMatchExactCount++;
  // Most of the time (roughly 5 out of every 6
  // times) this MaxValue estimate is exactly
  // right:
  quotient.setD( testIndex, maxValue );
  }
else
  {
  // MaxValue can't be zero here. If it was it
  // would already be low enough before it got
  // here.
  maxValue--;
  if( maxValue == 0 )
    throw "After decrement: MaxValue is zero.";

  testForDivide1.copy( quotient );
  testForDivide1.setD( testIndex, maxValue );
  intMath.multiplyTop( testForDivide1, divideBy );
  if( testForDivide1.paramIsGreaterOrEq(
                                      toDivide ))
    {
    // ToMatchDecCount++;
    quotient.setD( testIndex, maxValue );
    }
  else
    {
    // TestDivideBits is done as a last resort,
    // but it's rare.  But it does at least limit
    // it to a worst case scenario of trying 32
    // bits, rather than 4 billion or so
    // decrements.
    testDivideBits( maxValue,
                        true,
                        testIndex,
                        toDivide,
                        divideBy,
                        quotient,
                        remainder,
                        intMath );
    }

  // TestGap = MaxValue - LgQuotient.D[TestIndex];
  // if( TestGap > HighestToMatchGap )
    // HighestToMatchGap = TestGap;

  // HighestToMatchGap: 4,294,967,293
  // uint size:         4,294,967,295 uint
  }

// If it's done.
if( testIndex == 0 )
  {
  testForDivide1.copy( quotient );
  intMath.multiply( testForDivide1, divideByKeep );
  remainder.copy( toDivideKeep );
  intMath.subtract( remainder, testForDivide1 );
  if( divideByKeep.paramIsGreater( remainder ))
    throw "Remainder > DivideBy LongDivide3().";

  return;
  }

// Now do the rest of the digits.
testIndex--;
while( true )
  {
  testForDivide1.copy( quotient );
  // First Multiply() for each digit.
  intMath.multiply( testForDivide1, divideBy );

  if( toDivide.paramIsGreater( testForDivide1 ))
    throw "Problem in LongDivide3().";

  remainder.copy( toDivide );
  intMath.subtract( remainder, testForDivide1 );
  maxValue = remainder.getD( remainder.
                               getIndex()) << 32;
  Int32 checkIndex = remainder.getIndex() - 1;
  if( checkIndex > 0 )
    maxValue |= remainder.getD( checkIndex );

  denom = divideBy.getD( divideBy.getIndex());
  if( denom != 0 )
    maxValue = maxValue / denom;
  else
    maxValue = 0xFFFFFFFF;

  if( maxValue > 0xFFFFFFFF )
    maxValue = 0xFFFFFFFF;

  testForDivide1.copy( quotient );
  testForDivide1.setD( testIndex, maxValue );
  // There's a minimum of two full Multiply()
  // operations per digit.
  intMath.multiply( testForDivide1, divideBy );
  if( testForDivide1.paramIsGreaterOrEq(
                                    toDivide ))
    {
    // Most of the time this MaxValue estimate
    // is exactly right:
    // ToMatchExactCount++;
    quotient.setD( testIndex, maxValue );
    }
  else
    {
    maxValue--;
    testForDivide1.copy( quotient );
    testForDivide1.setD( testIndex, maxValue );
    intMath.multiply( testForDivide1, divideBy );
    if( testForDivide1.paramIsGreaterOrEq(
                                       toDivide ))
      {
      // ToMatchDecCount++;
      quotient.setD( testIndex, maxValue );
      }
    else
      {
      testDivideBits( maxValue,
                          false,
                          testIndex,
                          toDivide,
                          divideBy,
                          quotient,
                          remainder,
                          intMath );

      // TestGap = MaxValue - LgQuotient.
                  //D[TestIndex];
      // if( TestGap > HighestToMatchGap )
            // HighestToMatchGap = TestGap;
      }
    }

  if( testIndex == 0 )
    break;

  testIndex--;
  }

testForDivide1.copy( quotient );
intMath.multiply( testForDivide1, divideByKeep );
remainder.copy( toDivideKeep );
intMath.subtract( remainder, testForDivide1 );
if( divideByKeep.paramIsGreater( remainder ))
  throw "Remainder > DivideBy longDivide3().";

}
*/
