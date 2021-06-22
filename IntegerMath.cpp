// Copyright Eric Chauvin 2021.




#include "IntegerMath.h"
#include "Base10Number.h"
#include "CharBuf.h"
#include "Division.h"



IntegerMath::IntegerMath( void )
{
// This is something like 8 bytes times
// 1000 * 1000 which is 8 million bytes.
// The maximum default stack size is 8 megabytes.

// "For instance, to specify a 16MB stack
// you could do the following:"
// cc -Wl,-stack_size -Wl,0x1000000

signedD = new Int64[Integer::digitArraySize];
scratch = new Uint64[Integer::digitArraySize];
}


IntegerMath::~IntegerMath( void )
{
delete[] signedD;
delete[] scratch;
}


// The copy constructor.
IntegerMath::IntegerMath( const IntegerMath& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Copy constructor: IntegerMath.\n";
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
                               Integer& toTest,
                               SPrimes& sPrimes )
{
if( (toTest.getD( 0 ) & 1) == 0 )
  return 2; // It's divisible by 2.

for( Uint32 count = 1; count <
                  SPrimes::arrayLength; count++ )
  {
  // Is the prime a 32 bit number?
  // getMod32 would throw an exception.
  Uint64 aPrime = sPrimes.getPrimeAt( count );
  if( 0 == getMod32( toTest, aPrime ))
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

for( Int32 count = (Int32)last; count >= 0;
                                       count-- )
  {
  if( result.getD( (Uint32)count ) != 0 )
    {
    result.setIndex( (Uint32)count );
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

// paramIsGreater() handles positive and
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
  signedD[count] = (Int64)result.getD( count );

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

for( Int32 count = (Int32)lastR; count >= 0;
                                        count-- )
  {
  if( result.getD( (Uint32)count ) != 0 )
    {
    result.setIndex( (Uint32)count );
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
  {
  M.setV( column, 0, toMul *
                      result.getD( column ));
  }

// Add these up with a carry.
result.setD( 0, M.getV( 0, 0 ) & 0xFFFFFFFF );
Uint64 carry = M.getV( 0, 0 ) >> 32;
for( Uint32 column = 1; column <= last; column++ )
  {
  // This Test value does not overflow:
  // const ulong Test = ((ulong)0xFFFFFFFF *
  //    (ulong)(0xFFFFFFFF)) + 0xFFFFFFFF;

  Uint64 total = M.getV( column, 0 ) + carry;
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
                             Integer& from,
                             Uint64 toMul )
{
const Uint32 fromCopyIndex = from.getIndex();
result.setIndex( fromCopyIndex );
for( Uint32 column = 0; column <= fromCopyIndex;
                                       column++ )
  scratch[column] = toMul * from.getD( column );

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
  M.setV( column, 0, B0 * digit );
  // Column + 1 and Row is 1, so it's just like
  // pen and paper.
  M.setV( column + 1, 1, B1 * digit );
  }

// Since B1 is not zero, the index is set one
// higher.
result.incrementIndex();
M.setV( result.getIndex(), 0, 0 );

// Add these up with a carry.
result.setD( 0, M.getV( 0, 0 ) & 0xFFFFFFFF );
Uint64 carry = M.getV( 0, 0 ) >> 32;
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
    Uint64 mValue = M.getV( column, row );
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
      M.setV( column + row, row, 0 );
      }
    }
  else
    {
    Uint32 countMult = result.getIndex();
    for( Uint32 column = 0; column <= countMult;
                                        column++ )
      {
      M.setV( column + row, row,
                           toMul.getD( row ) *
                           result.getD( column ));
      }
    }
  }

// Add the columns up with a carry.
result.setD( 0, M.getV( 0, 0 ) & 0xFFFFFFFF );
Uint64 carry = M.getV( 0, 0 ) >> 32;
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
    totalRight += M.getV( column, row )
                                   & 0xFFFFFFFF;
    totalLeft += M.getV( column, row ) >> 32;
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



/*
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
*/


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

Integer toDivide;
toDivide.copy( from );

Integer quotient;
CharBuf cBuf;
while( !toDivide.isZero())
  {
  Uint32 digit = (Uint32)Division::
         shortDivideRem( toDivide, 10, quotient );
  toDivide.copy( quotient );
  // Ascii values go from '0' up to '9'.
  cBuf.appendChar( (char)('0' + digit) );
  }

if( from.getIsNegative() )
  cBuf.appendChar( '-' );

Str result = cBuf.getStr();
result.reverse();
return result;
}



/*
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
*/



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
  M.setV( column + resultIndex,
          resultIndex, 
          result.getD( resultIndex ) *
          toMul.getD( column ));

for( Uint32 column = 0; column < resultIndex;
                                       column++ )
  result.setD( column, 0 );

Uint64 carry = 0;
for( Uint32 column = 0; column <= toMulIndex;
                                       column++ )
  {
  Uint64 total = M.getV( column + resultIndex,
                         resultIndex) + carry;
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



/*
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

*/



Uint64 IntegerMath::getMod32( Integer& in,
                              Uint64 divisor )
{
if( divisor == 0 )
  throw "getMod32: divisor == 0.";

if( (divisor >> 32) != 0 )
  throw "getMod32: (DivideByU >> 32) != 0.";

if( in.getIndex() == 0 )
  {
  Uint64 result = in.getD( 0 ) % divisor;
  return result;
  }

const Uint32 last = in.getIndex();

for( Uint32 count = 0; count <= last; count++ )
  scratch[count] = in.getD( count );

Uint64 remainder = 0;
if( divisor <= scratch[last] )
  {
  Uint64 oneDigit = scratch[last];
  remainder = oneDigit % divisor;
  scratch[last] = remainder;
  }

for( Int32 count = (Int32)last; count >= 1;
                                        count-- )
  {
  Uint64 twoDigits = scratch[count];
  twoDigits <<= 32;
  twoDigits |= scratch[count - 1];
  remainder = twoDigits % divisor;

  // This is not necessary for just a remainder:
  // scratch[count] = 0;

  scratch[count - 1] = remainder;
  }

return remainder;
}



Uint64 IntegerMath::mod64FromTwoULongs( Uint64 p1,
                                  Uint64 p0,
                                  Uint64 divisor )
{
if( divisor <= 0xFFFFFFFFL )
  throw "mod64FromTwoULongs divisor <= ";

// This is never shifted more than 12 bits, so
// check to make sure there's room to shift it.
if( (divisor >> 52) != 0 )
  throw "divisor too big in mod64FromTwoULongs.";

if( p1 == 0 )
  return p0 % divisor;

//////////////////////////////////////////////
// (P1 * 2^64) + P0 is what the number is.
// Uint64 base = 1 << 32;

Uint64 part1 = p1 % divisor;
if( (divisor >> 40) == 0 )
  {
  // Then this can be done 24 bits at a time.
  part1 <<= 24;  // Times 2^24
  part1 = part1 % divisor;
  part1 <<= 24;  //  48
  part1 = part1 % divisor;
  part1 <<= 16;  // Brings it to 64
  part1 = part1 % divisor;
  }
else
  {
  part1 <<= 12;  // Times 2^12
  part1 = part1 % divisor;
  part1 <<= 12;  // Times 2^12
  part1 = part1 % divisor;
  part1 <<= 12;  // Times 2^12
  part1 = part1 % divisor;
  part1 <<= 12;  // Times 2^12 Brings it to 48.
  part1 = part1 % divisor;
  part1 <<= 8;  // Times 2^8
  part1 = part1 % divisor;
  part1 <<= 8;  // Times 2^8 Brings it to 64.
  part1 = part1 % divisor;
  }

// All of the above was just to get the P1 part
// of it, so now add P0:
return (part1 + p0) % divisor;
}



Uint64 IntegerMath::getMod64( Integer& in,
                              Uint64 divisor )
{
if( divisor == 0 )
  throw "getMod64: divisor == 0.";

if( (divisor & 0xFFFFFFFFL ) == 0 )
  throw "getMod64: Divisor too small.";

const Uint32 last = in.getIndex();

if( last == 0 )
  return in.getD( 0 ); // It's a 33+ bit divisor.

Uint64 digit1 = 0;
Uint64 digit0 = 0;
Uint64 remainder = 0;
if( last == 2 )
  {
  digit1 = in.getD( 2 );
  digit0 = in.getD( 1 ) << 32;
  digit0 |= in.getD( 0 );
  return mod64FromTwoULongs( digit1, digit0,
                                      divisor );
  }

if( last == 3 )
  {
  digit1 = in.getD( 3 ) << 32;
  digit1 |= in.getD( 2 );
  digit0 = in.getD( 1 ) << 32;
  digit0 |= in.getD( 0 );
  return mod64FromTwoULongs( digit1, digit0,
                                     divisor );
  }

for( Uint32 count = 0; count <= last; count++ )
  scratch[count] = in.getD( count );

Uint32 where = last;
while( true )
  {
  if( where <= 3 )
    {
    if( where < 2 ) // This can't happen.
      throw "GetMod64(): Where < 2.";

    if( where == 2 )
      {
      digit1 = scratch[2];
      digit0 = scratch[1] << 32;
      digit0 |= scratch[0];
      return mod64FromTwoULongs( digit1, digit0,
                                        divisor );
      }

    if( where == 3 )
      {
      digit1 = scratch[3] << 32;
      digit1 |= scratch[2];
      digit0 = scratch[1] << 32;
      digit0 |= scratch[0];
      return mod64FromTwoULongs( digit1, digit0,
                                       divisor );
      }
    }
  else
    {
    // The index is bigger than 3.
    // This part would get called at least once.
    digit1 = scratch[where] << 32;
    digit1 |= scratch[where - 1];
    digit0 = scratch[where - 2] << 32;
    digit0 |= scratch[where - 3];
    remainder = mod64FromTwoULongs( digit1, digit0,
                                  divisor );
    scratch[where] = 0;
    scratch[where - 1] = 0;
    scratch[where - 2] = remainder >> 32;
    scratch[where - 3] = remainder &
                                      0xFFFFFFFF;
    }

  where -= 2;
  }
}
