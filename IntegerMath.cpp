// Copyright Eric Chauvin 2021.



#include "IntegerMath.h"
#include "StIO.h"
#include "Base10Number.h"
#include "CharBuf.h"
#include "Division.h"



IntegerMath::IntegerMath( void )
{

}


// IntegerMath::~IntegerMath( void )


// The copy constructor.
IntegerMath::IntegerMath( const IntegerMath& in )
{
throw "Copy constructor: IntegerMath called.\n";
}


Uint64 IntegerMath::findULSqrRoot(
                                 Uint64 toMatch )
{
Uint64 oneBit = 0x80000000L; // 0x8000 0000
Uint64 result = 0;
for( Uint32 count = 0; count < 32; count++ )
  {
  Uint64 toTry = result | oneBit;
  if( (toTry * toTry) <= toMatch )
    result |= oneBit; // Then I want the bit.

  oneBit >>= 1;
  }

if( result == 0 )
  throw "FindULSqrRoot() Result was zero.";

// Test:
if( (result * result) > toMatch )
  throw "FindULSqrRoot() Result is too high.";

// This would overflow if Answer was 0xFFFFFFFF.
if( result < 0xFFFFFFFFL )
  {
  if( ((result + 1) * (result + 1)) <=
                                        toMatch )
    throw "FindULSqrRoot() Result is too low.";

  }

return result;
}



Uint64 IntegerMath::isDivisibleBySmallPrime(
                               Integer& toTest )
{
if( (toTest.getD( 0 ) & 1) == 0 )
  return 2; // It's divisible by 2.

for( Uint32 count = 1; count <
                  SPrimes::arrayLength; count++ )
  {
  // Is the prime a 32 bit number?
  // getMod32 would throw an exception.
  Uint64 aPrime = sPrimes.getPrimeAt( count );
  if( 0 == toTest.getMod32( aPrime ))
    return aPrime;

  }

// No small primes divide it.
return 0;
}



void IntegerMath::subtractULong( Integer& result,
                                 Uint64 toSub )
{
if( result.isULong())
  {
  Uint64 resultU = result.getAsULong();
  if( toSub > resultU )
    throw "IsULong() and (toSub > tesult).";

  resultU = resultU - toSub;
  result.setD( 0, resultU & 0xFFFFFFFF );
  result.setD( 1, resultU >> 32 );
  if( result.getD( 1 ) == 0 )
    result.setIndex( 0 );
  else
    result.setIndex( 1 );

  return;
  }

// If it got this far then Index is at least 2.
signedD[0] = (Int64)result.getD( 0 ) -
             (Int64)(toSub & 0xFFFFFFFF);
signedD[1] = (Int64)result.getD( 1 ) -
             (Int64)(toSub >> 32);
if( (signedD[0] >= 0) && (signedD[1] >= 0) )
  {
  // No need to reorganize it.
  result.setD( 0, (Uint64)signedD[0] );
  result.setD( 1, (Uint64)signedD[1] );
  return;
  }

const Uint32 last = result.getIndex();
for( Uint32 count = 2; count <= last; count++ )
  signedD[count] = (Int64)result.getD( count );

for( Uint32 count = 0; count < last; count++ )
  {
  if( signedD[count] < 0 )
    {
    signedD[count] += (Uint64)0xFFFFFFFF + 1;
    signedD[count + 1]--;
    }
  }

if( signedD[last] < 0 )
  throw "SubULong() SignedD[Index] < 0.";

for( Uint32 count = 0; count <= last; count++ )
  result.setD( count, (Uint64)signedD[count] );

for( Int32 count = last; count >= 0; count-- )
  {
  if( result.getD( count ) != 0 )
    {
    result.setIndex( count );
    return;
    }
  }

// If this was zero it wouldn't find a nonzero
// digit to set the Index to and it would end
// up down here.
result.setIndex( 0 );
}



void IntegerMath::add( Integer& result,
                       Integer& toAdd )
{
if( toAdd.isZero())
  return;

// The most common form.  They are both positive.
if( !result.getIsNegative() &&
    !toAdd.getIsNegative() )
  {
  result.add( toAdd );
  return;
  }

Integer tempAdd1;
Integer tempAdd2;

if( !result.getIsNegative() &&
     toAdd.getIsNegative() )
  {
  tempAdd1.copy( toAdd );
  tempAdd1.setIsNegative( false );
  if( tempAdd1.paramIsGreater( result ))
    {
    subtract( result, tempAdd1 );
    return;
    }
  else
    {
    subtract( tempAdd1, result );
    result.copy( tempAdd1 );
    result.setIsNegative( true );
    return;
    }
  }

if( result.getIsNegative() &&
    !toAdd.getIsNegative() )
  {
  tempAdd1.copy( result );
  tempAdd1.setIsNegative( false );
  tempAdd2.copy( toAdd );
  if( tempAdd1.paramIsGreater( tempAdd2 ))
    {
    subtract( tempAdd2, tempAdd1 );
    result.copy( tempAdd2 );
    return;
    }
  else
    {
    subtract( tempAdd1, tempAdd2 );
    result.copy( tempAdd2 );
    result.setIsNegative( true );
    return;
    }
  }

if( result.getIsNegative() &&
    toAdd.getIsNegative() )
  {
  tempAdd1.copy( result );
  tempAdd1.setIsNegative( false );
  tempAdd2.copy( toAdd );
  tempAdd2.setIsNegative( false );
  tempAdd1.add( tempAdd2 );
  result.copy( tempAdd1 );
  result.setIsNegative( true );
  return;
  }
}



void IntegerMath::subtract( Integer& result,
                            Integer& toSub )
{
// This checks that the sign is equal too.
if( result.isEqual( toSub ))
  {
  result.setToZero();
  return;
  }

Integer tempSub1;
Integer tempSub2;

// ParamIsGreater() handles positive and
// negative values, so if the parameter is
// more toward the positive side then it's
// true.  It's greater.
// The most common form.  They are both positive.
if( !result.getIsNegative() &&
    !toSub.getIsNegative() )
  {
  if( toSub.paramIsGreater( result ))
    {
    subtractPositive( result, toSub );
    return;
    }

  // toSub is bigger.
  tempSub1.copy( result );
  tempSub2.copy( toSub );
  subtractPositive( tempSub2, tempSub1 );
  result.copy( tempSub2 );
  result.setIsNegative( true );
  return;
  }

if( result.getIsNegative() &&
    !toSub.getIsNegative() )
  {
  tempSub1.copy( result );
  tempSub1.setIsNegative( false );
  tempSub1.add( toSub );
  result.copy( tempSub1 );
  result.setIsNegative( true );
  return;
  }

if( !result.getIsNegative() &&
    toSub.getIsNegative() )
  {
  tempSub1.copy( toSub );
  tempSub1.setIsNegative( false );
  result.add( tempSub1 );
  return;
  }

if( result.getIsNegative() &&
    toSub.getIsNegative() )
  {
  tempSub1.copy( result );
  tempSub1.setIsNegative( false );
  tempSub2.copy( toSub );
  tempSub2.setIsNegative( false );
  // -12 - -7 = -12 + 7 = -5
  // Comparing the positive numbers here.
  if( tempSub2.paramIsGreater( tempSub1 ))
    {
    subtractPositive( tempSub1, tempSub2 );
    result.copy( tempSub1 );
    result.setIsNegative( true );
    return;
    }

  // -7 - -12 = -7 + 12 = 5
  subtractPositive( tempSub2, tempSub1 );
  result.copy( tempSub2 );
  result.setIsNegative( false );
  return;
  }
}



void IntegerMath::subtractPositive(
                                Integer& result,
                                Integer& toSub )
{
if( toSub.isULong() )
  {
  subtractULong( result, toSub.getAsULong());
  return;
  }

if( toSub.getIndex() > result.getIndex() )
  throw "In Subtract() ToSub.Index > Index.";

Uint32 const last = toSub.getIndex();
for( Uint32 count = 0; count <= last; count++ )
  signedD[count] = (Int64)result.getD( count )
                  - (Int64)toSub.getD( count );

const Uint32 lastR = result.getIndex();

for( Uint32 count = last + 1; count <= lastR;
                                       count++ )
  signedD[count] = (Uint64)result.getD( count );

for( Uint32 count = 0; count < lastR; count++ )
  {
  if( signedD[count] < 0 )
    {
    signedD[count] += (Int64)0xFFFFFFFF + 1;
    signedD[count + 1]--;
    }
  }

if( signedD[lastR] < 0 )
  throw "Subtract() SignedD[Index] < 0.";

for( Uint32 count = 0; count <= lastR; count++ )
  result.setD( count, (Uint64)signedD[count] );

for( Int32 count = lastR; count >= 0; count-- )
  {
  if( result.getD( count ) != 0 )
    {
    result.setIndex( count );
    return;
    }
  }

// If it never found a non-zero digit it
// would get down to here.
result.setIndex( 0 );
}



void IntegerMath::multiplyUInt( Integer& result,
                                Uint64 toMul )
{
if( toMul == 0 )
  {
  result.setToZero();
  return;
  }

if( toMul == 1 )
  return;

const Uint32 last = result.getIndex();
for( Uint32 column = 0; column <= last; column++ )
  M[column][0] = toMul * result.getD( column );

// Add these up with a carry.
result.setD( 0, M[0][0] & 0xFFFFFFFF );
Uint64 carry = M[0][0] >> 32;
for( Uint32 column = 1; column <= last; column++ )
  {
  // This Test value does not overflow:
  // const ulong Test = ((ulong)0xFFFFFFFF *
  //    (ulong)(0xFFFFFFFF)) + 0xFFFFFFFF;

  Uint64 total = M[column][0] + carry;
  result.setD( column, total & 0xFFFFFFFF );
  carry = total >> 32;
  }

if( carry != 0 )
  {
  result.incrementIndex();
  result.setD( result.getIndex(), carry );
  }
}




Uint32 IntegerMath::multiplyUIntFromCopy(
                             Integer& result,
                             Integer& fromCopy,
                             Uint64 toMul )
{
const Uint32 fromCopyIndex = fromCopy.getIndex();
result.setIndex( fromCopyIndex );
for( Uint32 column = 0; column <= fromCopyIndex;
                                       column++ )
  scratch[column] = toMul * fromCopy.getD( column );

// Add these up with a carry.
result.setD( 0, scratch[0] & 0xFFFFFFFF );
Uint64 carry = scratch[0] >> 32;
for( Uint32 column = 1; column <= fromCopyIndex;
                                       column++ )
  {
  Uint64 total = scratch[column] + carry;
  result.setD( column, total & 0xFFFFFFFF );
  carry = total >> 32;
  }

if( carry != 0 )
  {
  result.incrementIndex();
  result.setD( fromCopyIndex + 1, carry );
  }

return result.getIndex();
}



void IntegerMath::multiplyULong( Integer& result,
                                 Uint64 toMul )
{
// Using compile-time checks, this one overflows:
// const ulong Test = ((ulong)0xFFFFFFFF + 1) *
// ((ulong)0xFFFFFFFF + 1);
// This one doesn't:
// const ulong Test = (ulong)0xFFFFFFFF *
// ((ulong)0xFFFFFFFF + 1);

if( result.isZero())
  return;

if( toMul == 0 )
  {
  result.setToZero();
  return;
  }

Uint64 B0 = toMul & 0xFFFFFFFF;
Uint64 B1 = toMul >> 32;
if( B1 == 0 )
  {
  multiplyUInt( result, B0 );
  return;
  }

// Since B1 is not zero:
if( (result.getIndex() + 1) >=
                         Integer::digitArraySize )
  throw "Overflow in MultiplyULong.";

Uint32 countTo = result.getIndex();
for( Uint32 column = 0; column <= countTo;
                                       column++ )
  {
  Uint64 digit = result.getD( column );
  M[column][0] = B0 * digit;
  // Column + 1 and Row is 1, so it's just like
  // pen and paper.
  M[column + 1][1] = B1 * digit;
  }

// Since B1 is not zero, the index is set one
// higher.
result.incrementIndex();
M[result.getIndex()][0] = 0;

// Add these up with a carry.
result.setD( 0, M[0][0] & 0xFFFFFFFF );
Uint64 carry = M[0][0] >> 32;
countTo = result.getIndex();
for( Uint32 column = 1; column <= countTo;
                                       column++ )
  {
  // This does overflow:
  // const ulong Test = ((ulong)0xFFFFFFFF *
  // (ulong)(0xFFFFFFFF))
  // + ((ulong)0xFFFFFFFF * (ulong)(0xFFFFFFFF));
  // Split the ulongs into right and left sides
  // so that they don't overflow.
  Uint64 totalLeft = 0;
  Uint64 totalRight = 0;
  // There's only the two rows for this.
  for( Uint32 row = 0; row <= 1; row++ )
    {
    Uint64 mValue = M[column][row];
    totalRight += mValue & 0xFFFFFFFF;
    totalLeft += mValue >> 32;
    }

  totalRight += carry;
  result.setD( column, totalRight & 0xFFFFFFFF );
  carry = totalRight >> 32;
  carry += totalLeft;
  }

if( carry != 0 )
  {
  result.incrementIndex();
  result.setD( result.getIndex(), carry );
  }
}



void IntegerMath::setMultiplySign(
                               Integer& result,
                               Integer& toMul )
{
if( result.getIsNegative() ==
    toMul.getIsNegative() )
  result.setIsNegative( false );
else
  result.setIsNegative( true );

}


void IntegerMath::multiply( Integer& result,
                            Integer& toMul )
{
if( result.isZero())
  return;

if( toMul.isULong())
  {
  multiplyULong( result, toMul.getAsULong());
  setMultiplySign( result, toMul );
  return;
  }

// It could never get here if ToMul is zero
// because getIsULong()
// would be true for zero.
Uint32 totalIndex = result.getIndex() +
                                toMul.getIndex();
if( totalIndex >= Integer::digitArraySize )
  throw "Multiply() overflow.";

Uint32 countTo = toMul.getIndex();
for( Uint32 row = 0; row <= countTo; row++ )
  {
  if( toMul.getD( row ) == 0 )
    {
    Uint32 countZeros = result.getIndex();
    for( Uint32 column = 0; column <= countZeros;
                                        column++ )
      {
      M[column + row][row] = 0;
      }
    }
  else
    {
    Uint32 countMult = result.getIndex();
    for( Uint32 column = 0; column <= countMult;
                                        column++ )
      {
      M[column + row][row] = toMul.getD( row ) *
                           result.getD( column );
      }
    }
  }

// Add the columns up with a carry.
result.setD( 0, M[0][0] & 0xFFFFFFFF );
Uint64 carry = M[0][0] >> 32;
Uint32 resultIndex = result.getIndex();
Uint32 mulIndex = toMul.getIndex();
for( Uint32 column = 1; column <= totalIndex;
                                      column++ )
  {
  Uint64 totalLeft = 0;
  Uint64 totalRight = 0;
  for( Uint32 row = 0; row <= mulIndex; row++ )
    {
    if( row > column )
      break;

    if( column > (resultIndex + row) )
      continue;

    // Split the ulongs into right and left sides
    // so that they don't overflow.
    totalRight += M[column][row] & 0xFFFFFFFF;
    totalLeft += M[column][row] >> 32;
    }

  totalRight += carry;
  result.setD( column, totalRight & 0xFFFFFFFF );
  carry = totalRight >> 32;
  carry += totalLeft;
  }

result.setIndex( totalIndex );
if( carry != 0 )
  {
  result.incrementIndex();
  result.setD( result.getIndex(), carry );
  }

setMultiplySign( result, toMul );
}



void IntegerMath::setFromStr( Integer& result,
                              Str& in )
{
if( in.getSize() < 1 )
  {
  result.setToZero();
  return;
  }

Base10Number base10N( in );
Integer tens;
Integer onePart;
base10N.setFromStr( in );
result.setFromULong( base10N.getD( 0 ));
tens.setFromULong( 10 );
const Uint32 last = base10N.getIndex();
for( Uint32 count = 1; count <= last; count++ )
  {
  onePart.setFromULong( base10N.getD( count ));
  multiply( onePart, tens );
  result.add( onePart );
  multiplyULong( tens, 10 );
  }
}



Str IntegerMath::toString10( Integer& from )
{
if( from.isULong())
  {
  Uint64 N = from.getAsULong();
  Str nS( N );
  if( from.getIsNegative() )
    {
    Str sign( "-" );
    Str both( sign, nS );
    return both;
    }
  else
    {
    return nS;
    }
  }

Integer toDivide( from );
Integer quotient;
CharBuf cBuf;
Uint32 commaCount = 0;
while( !toDivide.isZero())
  {
  Uint32 digit = (Uint32)Division::
         shortDivideRem( toDivide, 10, quotient );
  toDivide.copy( quotient );
  // Ascii values go from '0' up to '9'.
  cBuf.appendChar( (char)('0' + digit) );
  if( ((commaCount % 3) == 0) &&
       (commaCount != 0) )
    {
    cBuf.appendChar( ',' );
    }

  commaCount++;
  }

if( from.getIsNegative() )
  cBuf.appendChar( ',' );

Str result = cBuf.getStr();
result.reverse();
return result;
}



void IntegerMath::square( Integer& toSquare )
{
if( toSquare.getIndex() == 0 )
  {
  toSquare.square0();
  return;
  }

if( toSquare.getIndex() == 1 )
  {
  toSquare.square1();
  return;
  }

if( toSquare.getIndex() == 2 )
  {
  toSquare.square2();
  return;
  }

// Now Index is at least 3:
Uint32 doubleIndex = toSquare.getIndex() << 1;
if( doubleIndex >= Integer::digitArraySize )
  throw "Square() overflowed.";

const Uint32 last = toSquare.getIndex();
for( Uint32 row = 0; row <= last; row++ )
  {
  if( toSquare.getD( row ) == 0 )
    {
    for( Uint32 column = 0; column <= last;
                                       column++ )
      {
      M[column + row][row] = 0;
      }
    }
  else
    {
    for( Uint32 column = 0; column <= last;
                                      column++ )
      {
      M[column + row][row] =
                      toSquare.getD( row ) *
                      toSquare.getD( column );
      }
    }
  }

// Add the columns up with a carry.
toSquare.setD( 0, M[0][0] & 0xFFFFFFFF );
Uint64 carry = M[0][0] >> 32;
for( Uint32 column = 1; column <= doubleIndex;
                                       column++ )
  {
  Uint64 totalLeft = 0;
  Uint64 totalRight = 0;
  for( Uint32 row = 0; row <= column; row++ )
    {
    if( row > last )
      break;

    if( column > (last + row) )
      continue;

    totalRight += M[column][row] & 0xFFFFFFFF;
    totalLeft += M[column][row] >> 32;
    }

  totalRight += carry;
  toSquare.setD( column, totalRight & 0xFFFFFFFF );
  carry = totalRight >> 32;
  carry += totalLeft;
  }

toSquare.setIndex( doubleIndex );
if( carry != 0 )
  {
  toSquare.incrementIndex();
  toSquare.setD( toSquare.getIndex(), carry );
  }
}



// This is an optimization for multiplying when
// only the top digit of a number has been set
// and all of the other digits are zero.
void IntegerMath::multiplyTop( Integer& result,
                               Integer& toMul )
{
Uint32 totalIndex = result.getIndex() +
                             toMul.getIndex();
if( totalIndex >= Integer::digitArraySize )
  throw "MultiplyTop() overflow.";

// Just like Multiply() except that all the
// other rows are zero:
Uint32 toMulIndex = toMul.getIndex();
Uint32 resultIndex = result.getIndex();
for( Uint32 column = 0; column <= toMulIndex;
                                      column++ )
  M[column + resultIndex][resultIndex] =
                    result.getD( resultIndex ) *
                    toMul.getD( column );

for( Uint32 column = 0; column < resultIndex;
                                       column++ )
  result.setD( column, 0 );

Uint64 carry = 0;
for( Uint32 column = 0; column <= toMulIndex;
                                       column++ )
  {
  Uint64 total = M[column + resultIndex]
                           [resultIndex] + carry;
  result.setD( column + resultIndex,
                           total & 0xFFFFFFFF );
  carry = total >> 32;
  }

result.setIndex( totalIndex );
if( carry != 0 )
  {
  result.setIndex( result.getIndex() + 1 );
  if( result.getIndex() >=
                        Integer::digitArraySize )
    throw "MultiplyTop() overflow.";

  result.setD( result.getIndex(), carry );
  }
}



// This is another optimization.  This is used
// when the top digit is 1 and all of the other
// digits are zero.  This is effectively just a
// shift-left operation.
void IntegerMath::multiplyTopOne( Integer& result,
                                  Integer& toMul )
{
Uint32 totalIndex = result.getIndex() +
                                toMul.getIndex();
if( totalIndex >= Integer::digitArraySize )
  throw "MultiplyTopOne() overflow.";

Uint32 toMulIndex = toMul.getIndex();
Uint32 resultIndex = result.getIndex();
for( Uint32 column = 0; column <= toMulIndex;
                                       column++ )
  result.setD( column + resultIndex,
                            toMul.getD( column ));

for( Uint32 column = 0; column < resultIndex;
                                       column++ )
  result.setD( column, 0 );

// No Carrys need to be done.
result.setIndex( totalIndex );
}


// In the SquareRoot() method SqrRoot.Index is
// half of Square.Index.  Compare this to the
// Square() method where the Carry might or
// might not increment the index to an odd number.
// (So if the Index was 5 its square root would
// have an Index of 5 / 2 = 2.)
// The SquareRoot1() method uses FindULSqrRoot()
// either to find the whole answer, if it's a
// small number, or it uses it to find the top
// part.  Then from there it goes on to a bit by
// bit search with TestSqrtBits().

bool IntegerMath::squareRoot( Integer& fromSqr,
                          Integer& sqrRoot )
{
Uint64 toMatch;
if( fromSqr.isULong() )
  {
  toMatch = fromSqr.getAsULong();
  sqrRoot.setD( 0, findULSqrRoot( toMatch ));
  sqrRoot.setIndex( 0 );
  if( (sqrRoot.getD(0 ) * sqrRoot.getD( 0 )) ==
                                        toMatch )
    return true;
  else
    return false;

  }

Uint32 testIndex = fromSqr.getIndex() >> 1;
sqrRoot.setDigitAndClear( testIndex, 1 );
if( (testIndex << 1) > (fromSqr.getIndex() - 1) )
  {
  toMatch = fromSqr.getD( fromSqr.getIndex());
  }
else
  {
  toMatch = fromSqr.getD( fromSqr.getIndex()) << 32;
  toMatch |= fromSqr.getD( fromSqr.getIndex() - 1 );
  }

sqrRoot.setD( testIndex, findULSqrRoot( toMatch ));
testIndex--;
while( true )
  {
  searchSqrtXPart( testIndex, fromSqr, sqrRoot );
  if( testIndex == 0 )
    break;

  testIndex--;
  }

// Avoid squaring the whole thing to see if
// it's an exact square root:
if( ((sqrRoot.getD( 0 ) * sqrRoot.getD( 0 )) &
               0xFFFFFFFF) != fromSqr.getD( 0 ))
  return false;

Integer testForSquareRoot;

testForSquareRoot.copy( sqrRoot );
square( testForSquareRoot );
if( fromSqr.isEqual( testForSquareRoot ))
  return true;
else
  return false;

}




void IntegerMath::searchSqrtXPart(
                            Uint32 testIndex,
                            Integer& fromSqr,
                            Integer& sqrRoot )
{
// B is the Big part of the number that has
// already been found.
// S = (B + x)^2
// S = B^2 + 2Bx + x^2
// S - B^2 = 2Bx + x^2
// R = S - B^2
// R = 2Bx + x^2
// R = x(2B + x)

Integer sqrtXPartTest1;
Integer sqrtXPartTest2;
Integer sqrtXPartDiff;
Integer sqrtXPartTwoB;
Integer sqrtXPartR2;

sqrtXPartTest1.copy( sqrRoot ); // B
square( sqrtXPartTest1 ); // B^2
sqrtXPartDiff.copy( fromSqr );
subtract( sqrtXPartDiff, sqrtXPartTest1 );
                                      // S - B^2
sqrtXPartTwoB.copy( sqrRoot ); // B
sqrtXPartTwoB.shiftLeft( 1 ); // Times 2 for 2B.
sqrtXPartTest1.copy( sqrtXPartTwoB );
Uint64 testBits = sqrtXPartTest1.getD(
                      sqrtXPartTest1.getIndex());
Uint32 shiftBy = Division::findShiftBy( testBits );
sqrtXPartR2.copy( sqrtXPartDiff );
// Multiply the numerator and the denominator
sqrtXPartR2.shiftLeft( shiftBy );
sqrtXPartTest1.shiftLeft( shiftBy );

Uint64 highest = 0;
if( sqrtXPartR2.getIndex() == 0 )
  {
  highest = sqrtXPartR2.getD(
                         sqrtXPartR2.getIndex());
  }
else
  {
  highest = sqrtXPartR2.getD(
                    sqrtXPartR2.getIndex()) << 32;
  highest |= sqrtXPartR2.getD(
                    sqrtXPartR2.getIndex() - 1 );
  }

Uint64 denom = sqrtXPartTest1.getD(
                     sqrtXPartTest1.getIndex());
if( denom == 0 )
  highest = 0xFFFFFFFF;
else
  highest = highest / denom;

if( highest == 0 )
  {
  sqrRoot.setD( testIndex, 0 );
  return;
  }

if( highest > 0xFFFFFFFF )
  highest = 0xFFFFFFFF;

Uint32 bitTest = 0x80000000;
Uint64 xDigit = 0;
Uint64 tempXDigit = 0;
for( Uint32 bitCount = 0; bitCount < 32;
                                      bitCount++ )
  {
  tempXDigit = xDigit | bitTest;
  if( tempXDigit > highest )
    {
    bitTest >>= 1;
    continue;
    }

  sqrtXPartTest1.copy( sqrtXPartTwoB );
  sqrtXPartTest1.setD( testIndex, tempXDigit );
                                       // 2B + x
  sqrtXPartTest2.setDigitAndClear( testIndex,
                           tempXDigit ); // Set X.
  multiplyTop( sqrtXPartTest2, sqrtXPartTest1 );
  if( sqrtXPartTest2.paramIsGreaterOrEq(
                                 sqrtXPartDiff ))
    xDigit |= bitTest; // Then keep the bit.

  bitTest >>= 1;
  }

sqrRoot.setD( testIndex, xDigit );
}



bool IntegerMath::isFermatPrime( Integer& toTest,
                                 Uint32 howMany )
{
// Also see Rabin-Miller test.
// Also see Solovay-Strassen test.
// Use bigger primes for Fermat test because the
// modulus can't be too small.  And also it's
// more likely to be congruent to 1 with a very
// small modulus.  In other words it's a lot more
// likely to appear to be a prime when it isn't.
// This Fermat primality test is usually
// described as using random primes to test with,
// and you could do it that way too.
// A common way of doing this is to use a
// multiple of several primes as the base, like
// 2 * 3 * 5 * 7 = 210.
// Halfway down the array.
Uint32 startAt = SPrimes::arrayLength >> 1;

for( Uint32 count = startAt; count <
                   (howMany + startAt); count++ )
  {
  if( !isFermatPrimeForOneValue( toTest,
                   sPrimes.getPrimeAt( count )))
    {
    // It is definitely not a prime.
    return false;
    }
  }

// It _might_ be a prime if it passed this test.
// Increasing HowMany increases the probability
// that it's a prime.
return true;
}




bool IntegerMath::isFermatPrimeForOneValue(
                   Integer& toTest, Uint64 base )
{
// Assume ToTest is not a small number.  (Not
// the size of a small prime.)
// Normally it would be something like a 1024
// bit number or bigger, but I assume it's at
// least bigger than a 32 bit number.
// Assume this has already been checked to
// see if it's divisible by a small prime.
// A has to be coprime to P and it is here
// because ToTest is not divisible by a small
// prime.
// Fermat's little theorem:
// A ^ (P - 1) is congruent to 1 mod P if P
// is a prime.
// Or: A^P - A is congrunt to A mod P.
// If you multiply A by itself P times then
// divide it by P, the remainder is A.
//  (A^P / P)
// 5^3 = 125.  125 - 5 = 120.  A multiple of 5.
// 2^7 = 128.  128 - 2 = 7 * 18 (a multiple of 7.)

Integer fermat1;
fermat1.copy( toTest );
subtractULong( fermat1, 1 );
testFermat.setFromULong( base );



/*
 ===========
// ModularPower( Result, Exponent, Modulus, UsePresetBaseArray )

ModReduction.ModularPower( TestFermat, Fermat1, ToTest, false );
    // if( !TestFermat.IsEqual( Fermat2 ))
      // throw( new Exception( "!TestFermat.IsEqual( Fermat2 )." ));

    if( TestFermat.IsOne())
      return true; // It passed the test. It _might_ be a prime.
    else
      return false; // It is _definitely_ a composite number.
*/
}
