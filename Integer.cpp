// Copyright Eric Chauvin 2021.



#include "Integer.h"
#include "CharBuf.h"
#include "RandomCrypto.h"
#include "Uint8Array.h"


Integer::Integer( void )
{
D = new Uint64[digitArraySize];
scratch = new Uint64[digitArraySize];

setToZero();
}


// The copy constructor.
Integer::Integer( const Integer& in )
{
throw "Don't use the Integer copy constructor.";
}


Integer::~Integer( void )
{
delete[] D;
delete[] scratch;
}




void Integer::incrementIndex( void )
{
index++;
if( index >= digitArraySize )
  throw "Integer IncrementIndex() overflow.";

}


/*
void Integer::setToMaxValue( void )
{
isNegative = false;
index = digitArraySize - 1;
for( Uint32 count = 0; count <=
                    digitArraySize - 1; count++ )
  D[count] = 0xFFFFFFFF;

}
*/


void Integer::setFromULong( Uint64 toSet )
{
isNegative = false;

// If toSet was zero then D[0] would be zero and
// index would be zero.
D[0] = toSet & 0xFFFFFFFF;
D[1] = toSet >> 32;

if( D[1] == 0 )
  index = 0;
else
  index = 1;

}



void Integer::copy( Integer& from )
{
isNegative = from.isNegative;

const Uint32 last = from.index;

index = last;
for( Uint32 count = 0; count <= last; count++ )
      D[count] = from.D[count];

}


/*
void Integer::copyFromP( const Integer* copyFrom )
{
// Like: copyFromP( this );

isNegative = copyFrom->isNegative;
index = copyFrom->index;
const Uint32 last = copyFrom->index;
for( Uint32 count = 0; count <= last; count++ )
      D[count] = copyFrom->D[count];

}
*/


void Integer::copyUpTo( const Integer& from,
                        Uint32 where )
{
isNegative = from.isNegative;
index = where;
for( Uint32 count = 0; count <= where; count++ )
  D[count] = from.D[count];

}


/*
bool Integer::isEqualToULong( Uint64 toTest )
{
if( isNegative )
  return false;

if( index > 1 )
  return false;

if( D[0] != (toTest & 0xFFFFFFFF))
  return false;

Uint64 shifted = toTest >> 32;
if( index == 0 )
  {
  if( shifted == 0 )
    return true;
  else
    return false;

  }

if( shifted != D[1] )
  return false;

return true;
}
*/



bool Integer::isEqual( Integer& x )
{
if( isNegative != x.isNegative )
  return false;

if( D[0] != x.D[0] )
  return false;

if( index != x.index )
  return false;

// Starting from 1 because when the numbers
// are close the upper digits are the same, but
// the smaller digits are usually different.
// So it can find digits that are different
// sooner this way.
for( Uint32 count = 1; count <= index; count++ )
  {
  if( D[count] != x.D[count] )
    return false;

  }

return true;
}



bool Integer::isULong( void )
{
if( isNegative )
  return false;

if( index > 1 )
  return false;

return true;
}




Uint64 Integer::getAsULong( void )
{
// This is normally used after calling isULong().
// It is assumed here that it is a ulong.
if( index == 0 ) // Then D[1] is undefined.
  return D[0];

Uint64 result = D[1] << 32;
result |= D[0];
return result;
}



bool Integer::paramIsGreater( Integer& x )
{
if( isNegative )
  throw "ParamIsGreater() can't be negative.";

if( x.isNegative )
  throw "ParamIsGreater() can't be negative (2).";

if( index != x.index )
  {
  if( x.index > index )
    return true;
  else
    return false;

  }

// Indexes are the same:
for( Int32 count = index; count >= 0; count-- )
  {
  if( D[count] != x.D[count] )
    {
    if( x.D[count] > D[count] )
      return true;
    else
      return false;

    }
  }

return false; // It was equal, but not greater.
}



bool Integer::paramIsGreaterOrEq( Integer& x )
{
if( isEqual( x ))
  return true;

return paramIsGreater( x );
}


/*
void Integer::increment( void )
{
D[0] += 1;
if( (D[0] >> 32) == 0 )
  {
  // If there's nothing to Carry then no
  // reorganization is needed.
  return;
  }

Uint64 carry = D[0] >> 32;
D[0] = D[0] & 0xFFFFFFFF;
for( Uint32 count = 1; count <= index; count++ )
  {
  Uint64 total = carry + D[count];
  D[count] = total & 0xFFFFFFFF;
  carry = total >> 32;
  }

if( carry != 0 )
  {
  index++;
  if( index >= digitArraySize )
    throw  "Integer.Increment() overflow.";

  D[index] = carry;
  }
}
*/



void Integer::addULong( Uint64 toAdd )
{
D[0] += toAdd & 0xFFFFFFFF;
if( index == 0 ) // Then D[1] would be an
  {              // undefined value.
  D[1] = toAdd >> 32;
  if( D[1] != 0 )
    index = 1;

  }
else
  {
  D[1] += toAdd >> 32;
  }

if( (D[0] >> 32) == 0 )
  {
  // If there's nothing to Carry then no
  // reorganization is needed.
  if( index == 0 )
    return; // Nothing to Carry.

  if( (D[1] >> 32) == 0 )
    return; // Nothing to Carry.

  }

Uint64 carry = D[0] >> 32;
D[0] = D[0] & 0xFFFFFFFF;
for( Uint32 count = 1; count <= index; count++ )
  {
  Uint64 total = carry + D[count];
  D[count] = total & 0xFFFFFFFF;
  carry = total >> 32;
  }

if( carry != 0 )
  {
  index++;
  if( index >= digitArraySize )
    throw "Integer.AddULong() overflow.";

  D[index] = carry;
  }
}




void Integer::add( Integer& toAdd )
{
// There is a separate IntegerMath.Add() that
// is a wrapper to handle negative numbers too.
// if( isNegative )
// if( toAdd.isNegative )

if( toAdd.isULong() )
  {
  addULong( toAdd.getAsULong() );
  return;
  }

Uint32 localIndex = index;
const Uint32 localToAddIndex = toAdd.index;
if( localIndex < toAdd.index )
  {
  for( Uint32 count = localIndex + 1;
              count <= localToAddIndex; count++ )
    D[count] = toAdd.D[count];

  for( Uint32 count = 0; count <= localIndex;
                                      count++ )
    D[count] += toAdd.D[count];

  index = toAdd.index;
  }
else
  {
  for( Uint32 count = 0; count <= localToAddIndex;
                                         count++ )
    D[count] += toAdd.D[count];

  }

// After they've been added, reorganize it.
Uint64 carry = D[0] >> 32;
D[0] = D[0] & 0xFFFFFFFF;
localIndex = index;
for( Uint32 count = 1; count <= localIndex;
                                        count++ )
  {
  Uint64 total = carry + D[count];
  D[count] = total & 0xFFFFFFFF;
  carry = total >> 32;
  }

if( carry != 0 )
  {
  index++;
  if( index >= digitArraySize )
    throw "Integer.add() overflow.";

  D[index] = carry;
  }
}



/*
// This is an optimization for small squares.
void Integer::square0( void )
{
// If this got called then Index is 0.
Uint64 square = D[0] * D[0];
D[0] = square & 0xFFFFFFFF;
D[1] = square >> 32;
if( D[1] != 0 )
  index = 1;

}



void Integer::square1( void )
{
// If this got called then Index is 1.
Uint64 D0 = D[0];
Uint64 D1 = D[1];

// If you were multiplying 23 * 23 on paper
// it would look like:
//                            2     3
//                            2     3
//                           3*2   3*3
//                     2*2   2*3

// And then you add up the columns.
//                           D1    D0
//                           D1    D0
//                         M1_0  M0_0
//                   M2_1  M1_1

// Top row:
Uint64 M0_0 = D0 * D0;
Uint64 M1_0 = D0 * D1;

// Second row:
// ulong M1_1 = M1_0; // Avoiding D1 * D0 again.
Uint64 M2_1 = D1 * D1;

// Add them up:
D[0] = M0_0 & 0xFFFFFFFF;
Uint64 carry = M0_0 >> 32;

// This test will cause an overflow exception:
// ulong TestBits = checked( (ulong)0xFFFFFFFF *
                   //       (ulong)0xFFFFFFFF );
// ulong TestCarry = TestBits >> 32;
// TestBits = checked( TestBits + TestBits );
// TestBits = checked( TestBits + TestCarry );
// To avoid an overflow, split the ulongs into
// left and right halves and then add them up.
// D[1] = M1_0 + M1_1
Uint64 M0Right = M1_0 & 0xFFFFFFFF;
Uint64 M0Left = M1_0 >> 32;

// Avoiding a redundancy:
// M1_1 is the same as M1_0.
// ulong M1Right = M1_1 & 0xFFFFFFFF;
// ulong M1Left = M1_1 >> 32;
// ulong Total = M0Right + M1Right + Carry;

Uint64 total = M0Right + M0Right + carry;
D[1] = total & 0xFFFFFFFF;
carry = total >> 32;
carry += M0Left + M0Left;
total = (M2_1 & 0xFFFFFFFF) + carry;
D[2] = total & 0xFFFFFFFF;
carry = total >> 32;
carry += (M2_1 >> 32);
index = 2;
if( carry != 0 )
  {
  index++;
  D[3] = carry;
  }

// Bitwise multiplication with two bits is:
//       1  1
//       1  1
//     ------
//       1  1
//    1  1
// ----------
// 1  0  0  1
// Biggest bit is at position 3 (zero based index).
// Adding Indexes: (1 + 1) + 1.

//       1  0
//       1  0
//       0  0
//    1  0
//    1  0  0
// Biggest bit is at 2.
// Adding Indexes: (1 + 1).

// 7 * 7 = 49
//                 1  1  1
//                 1  1  1
//                --------
//                 1  1  1
//              1  1  1
//           1  1  1
//          --------------
//        1  1  0  0  0  1
//       32 16           1 = 49
// Biggest bit is at 5 (2 + 2) + 1.
// The highest bit is at either index +
// index or it's at index + index + 1.

// For this Integer class the Index might have to
// be incremented once for a Carry, but not more
// than once.
}



void Integer::square2( void )
{
// If this got called then Index is 2.
Uint64 D0 = D[0];
Uint64 D1 = D[1];
Uint64 D2 = D[2];

//                   M2_0   M1_0  M0_0
//            M3_1   M2_1   M1_1
//     M4_2   M3_2   M2_2

// Top row:
Uint64 M0_0 = D0 * D0;
Uint64 M1_0 = D0 * D1;
Uint64 M2_0 = D0 * D2;

// Second row:
// ulong M1_1 = M1_0;
Uint64 M2_1 = D1 * D1;
Uint64 M3_1 = D1 * D2;

// Third row:
// ulong M2_2 = M2_0;
// ulong M3_2 = M3_1;
Uint64 M4_2 = D2 * D2;

// Add them up:
D[0] = M0_0 & 0xFFFFFFFF;
Uint64 carry = M0_0 >> 32;

// D[1]
Uint64 M0Right = M1_0 & 0xFFFFFFFF;
Uint64 M0Left = M1_0 >> 32;
// ulong M1Right = M1_1 & 0xFFFFFFFF;
// ulong M1Left = M1_1 >> 32;
Uint64 total = M0Right + M0Right + carry;
D[1] = total & 0xFFFFFFFF;
carry = total >> 32;
carry += M0Left + M0Left;

// D[2]
M0Right = M2_0 & 0xFFFFFFFF;
M0Left = M2_0 >> 32;
Uint64 M1Right = M2_1 & 0xFFFFFFFF;
Uint64 M1Left = M2_1 >> 32;
// ulong M2Right = M2_2 & 0xFFFFFFFF;
// ulong M2Left = M2_2 >> 32;
total = M0Right + M1Right + M0Right + carry;
D[2] = total & 0xFFFFFFFF;
carry = total >> 32;
carry += M0Left + M1Left + M0Left;

// D[3]
M1Right = M3_1 & 0xFFFFFFFF;
M1Left = M3_1 >> 32;
// M2Right = M3_2 & 0xFFFFFFFF;
// M2Left = M3_2 >> 32;
total = M1Right + M1Right + carry;
D[3] = total & 0xFFFFFFFF;
carry = total >> 32;
carry += M1Left + M1Left;

// D[4]
Uint64 M2Right = M4_2 & 0xFFFFFFFF;
Uint64 M2Left = M4_2 >> 32;
total = M2Right + carry;
D[4] = total & 0xFFFFFFFF;
carry = total >> 32;
carry += M2Left;
index = 4;
if( carry != 0 )
  {
  index++;
  D[5] = carry;
  }
}
*/


void Integer::shiftLeft( Uint32 shiftBy )
{
// This one is not meant to shift more than 32
// bits at a time.  Obviously you could call it
// several times.
// Or put a wrapper function around this that
// calls it several times.
if( shiftBy > 32 )
      throw "ShiftBy > 32 on ShiftLeft.";

Uint64 carry = 0;
for( Uint32 count = 0; count <= index; count++ )
  {
  Uint64 digit = D[count];
  digit <<= shiftBy;
  D[count] = digit & 0xFFFFFFFF;
  D[count] |= carry;
  carry = digit >> 32;
  }

if( carry != 0 )
  {
  index++;
  if( index >= digitArraySize )
    throw "ShiftLeft overflowed.";

  D[index] = carry;
  }
}




void Integer::shiftRight( Uint32 shiftBy )
{
if( shiftBy > 32 )
  throw "ShiftBy > 32 on ShiftRight.";

Uint64 carry = 0;
for( Int32 count = index; count >= 0; count-- )
  {
  Uint64 digit = D[count] << 32;
  digit >>= shiftBy;
  D[count] = digit >> 32;
  D[count] |= carry;
  carry = digit & 0xFFFFFFFF;
  }

if( D[index] == 0 )
  {
  if( index > 0 )
    index--;

  }

// Let it shift bits over the edge.
// if( Carry != 0 )
  // throw "ShiftRight() Carry not zero.";

}




// This is used in some algorithms to set one
// particular digit and have all other digits set
// to zero.
void Integer::setDigitAndClear( Uint32 where,
                                   Uint64 toSet )
{
// For testing:
// This would lead to an undefined number that's
// zero but not zero since the Index isn't zero.
if( (toSet == 0) && (where != 0) )
  throw "setDigitAndClear() with bad zero.";

if( (toSet >> 32) != 0 )
  throw "setDigitAndClear() Bad stuff...";

index = where;
D[index] = toSet;
for( Uint32 count = 0; count < index; count++ )
  D[count] = 0;

}



bool Integer::makeRandomOdd( Uint32 setToIndex )
{
isNegative = false;
if( setToIndex > (digitArraySize - 3))
  throw "MakeRandomOdd index is too high.";

Uint32 howManyBytes = (setToIndex * 4) + 4;

Uint8Array u8a;
RandomCrypto::makeRandomBytes( u8a,
                                howManyBytes );

index = setToIndex;
Uint32 where = 0;
for( Uint32 count = 0; count <= index; count++ )
  {
  Uint64 digit = u8a.valAt( where );
  digit <<= 8;
  digit |= u8a.valAt( where + 1 );
  digit <<= 8;
  digit |= u8a.valAt( where + 2 );
  digit <<= 8;
  digit |= u8a.valAt( where + 3 );
  D[count] = digit;
  where += 4;
  }

// Make sure there isn't a zero at the top.
if( D[index] == 0 )
  throw "zero at top of random bytes.";

if( (D[index] >> 24) == 0 )
  throw "zero at very top of random bytes.";

// Test:
for( Uint32 count = 0; count <= index; count++ )
  {
  if( (D[count] >> 32) != 0 )
    throw "(D[Count] >> 32) != 0 MakeRandom().";

  }

D[0] |= 1; // Make it odd.
return true;
}



/*
void Integer::setOneDValueFromChar( Uint64 toSet,
                Uint32 position, Uint32 offset )
{
// These are ASCII values so they're between 32
// and 127.
if( position >= digitArraySize )
  return;

if( offset == 1 )
  toSet <<= 8;

if( offset == 2 )
  toSet <<= 16;

if( offset == 3 )
  toSet <<= 24;

// This assumes I'm setting them from zero upward.
if( offset == 0 )
  D[position] = toSet;
else
  D[position] |= toSet;

if( index < position )
  index = position;

}



char Integer::getOneCharFromDValue(
                Uint32 position, Uint32 offset )
{
// These are ASCII values so they're between 32
// and 127.
if( position >= digitArraySize )
  return (char)0;

if( offset == 0 )
  return (char)(D[position] & 0xFF);

if( offset == 1 )
  return (char)((D[position] >> 8) & 0xFF);

if( offset == 2 )
  return (char)((D[position] >> 16) & 0xFF);

if( offset == 3 )
  return (char)((D[position] >> 24) & 0xFF);

return (char)0; // This should never happen.
}


bool Integer::setFromAsciiStr( Str& in )
{
isNegative = false;
index = 0;
const Uint32 inLen = in.getSize();

if( inLen > (digitArraySize - 3))
  return false;

for( Uint32 count = 0; count < digitArraySize;
                                       count++ )
  D[count] = 0;

Uint32 oneChar = 0;
Uint32 position = 0;
Uint32 offset = 0;
for( Uint32 count = 0; count < inLen; count++ )
  {
  oneChar = in.charAt( count );
  setOneDValueFromChar( oneChar, position,
                                        offset );
  if( offset == 3 )
    position++;

  offset++;
  offset = offset % 4;
  // offset = offset & 0x3;
  }

return true;
}



Str Integer::getAsciiStr( void )
{
CharBuf cBuf;
for( Uint32 count = 0; count <= index; count++ )
  {
  Uint32 offset = 0;
  char oneChar = getOneCharFromDValue( count,
                                         offset );
  if( oneChar >= ' ' )
    cBuf.appendChar( oneChar );

  offset = 1;
  oneChar = getOneCharFromDValue( count, offset );
  // It could be missing upper characters at
  // the top, so they'd be zero.
  if( oneChar >= ' ' )
    cBuf.appendChar( oneChar );

  offset = 2;
  oneChar = getOneCharFromDValue( count, offset );
  if( oneChar >= ' ' )
    cBuf.appendChar( oneChar );

  offset = 3;
  oneChar = getOneCharFromDValue( count, offset );
  if( oneChar >= ' ' )
    cBuf.appendChar( oneChar );

  }

// StIO::printFS(
//        "Before two copy constructors.\n" );

return cBuf.getStr();
}




void Integer::setOneDValueFromByte( Uint64 toSet,
                  Uint32 setIndex, Uint32 offset )
{
if( setIndex >= digitArraySize )
  throw "SetIndex >= digitArraySize. setOneVal";

if( offset == 1 )
  toSet <<= 8;

if( offset == 2 )
  toSet <<= 16;

if( offset == 3 )
  toSet <<= 24;

// This assumes I'm setting them from zero upward.
// So if the position is zero it's not ORed with
// the value at D.
if( offset == 0 )
  D[setIndex] = toSet;
else
  D[setIndex] |= toSet;

if( index < setIndex )
  index = setIndex;

}



char Integer::getOneByteFromDValue(
                  Uint32 atIndex, Uint32 offset )
{
if( atIndex >= digitArraySize )
  throw "atIndex >= digitArraySize getOneByte.";

if( offset == 0 )
  return (char)(D[atIndex] & 0xFF);

if( offset == 1 )
  return (char)((D[atIndex] >> 8) & 0xFF);

if( offset == 2 )
  return (char)((D[atIndex] >> 16) & 0xFF);

if( offset == 3 )
  return (char)((D[atIndex] >> 24) & 0xFF);

throw "offset not right in GetOneByteFromDValue.";
}




// Because of the standards used with TLS,
// this will typically have one leading zero
// byte so that it doesn't get confused with
// a negative sign bit.  Sometimes it will,
// sometimes it won't.
void Integer::setFromBigEndianByteArray(
                              Uint8Array& U8Ar )
{
if( U8Ar.isAllZero())
  {
  setToZero();
  return;
  }

const Uint32 howMany = U8Ar.getLast();

if( howMany > (digitArraySize - 3))
  throw "digitArraySize SetFromBigEndian";

isNegative = false;
index = 0;

for( Uint32 count = 0; count < digitArraySize;
                                        count++ )
  D[count] = 0;

U8Ar.reverse(); // Now the least significant
                // byte is at zero.
Uint32 offset = 0;
Uint32 setIndex = 0;
for( Uint32 count = 0; count < howMany; count++ )
  {
  Uint32 toSet = U8Ar.valAt( count );
  setOneDValueFromByte( toSet, setIndex, offset );
  offset++;
  if( (offset & 3) == 0 )
    {
    offset = 0;
    setIndex++;
    }
  }

// Make sure it doesn't have leading zeros.
for( Int32 count = index; count >= 0; count-- )
  {
  if( D[count] != 0 )
    {
    index = count;
    break;
    }
  }
}


void Integer::getBigEndianByteArray(
                             Uint8Array& toGet )
{
toGet.clear();

for( Uint32 count = 0; count <= index; count++ )
  {
  for( Uint32 offset = 0; offset < 4; offset++ )
    {
    Uint8 oneByte = getOneByteFromDValue( count,
                                       offset );
    toGet.appendVal( oneByte );
    }
  }

toGet.reverse();

// Now the most significant byte is at Result[0].
// toGet might have leading zero bytes here.
}



Uint64 Integer::mod64FromTwoULongs( Uint64 p1,
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
*/


Uint64 Integer::getMod32( Uint64 divisor )
{
if( divisor == 0 )
  throw "getMod32: divisor == 0.";

if( (divisor >> 32) != 0 )
  throw "getMod32: (DivideByU >> 32) != 0.";

if( index == 0 )
  {
  Uint64 result = D[0] % divisor;
  return result;
  }

for( Uint32 count = 0; count < index; count++ )
  scratch[count] = D[count];

Uint64 remainder = 0;
if( divisor <= scratch[index] )
  {
  Uint64 oneDigit = scratch[index];
  remainder = oneDigit % divisor;
  scratch[index] = remainder;
  }

for( Int32 count = index; count >= 1; count-- )
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



/*
Uint64 Integer::getMod64( Uint64 divisor )
{
if( divisor == 0 )
  throw "getMod64: divisor == 0.";

if( (divisor & 0xFFFFFFFFL ) == 0 )
  throw "getMod64: Divisor too small.";

if( index == 0 )
  return D[0]; // It's a 33+ bit divisor.

Uint64 digit1 = 0;
Uint64 digit0 = 0;
Uint64 remainder = 0;
if( index == 2 )
  {
  digit1 = D[2];
  digit0 = D[1] << 32;
  digit0 |= D[0];
  return mod64FromTwoULongs( digit1, digit0,
                                      divisor );
  }

if( index == 3 )
  {
  digit1 = D[3] << 32;
  digit1 |= D[2];
  digit0 = D[1] << 32;
  digit0 |= D[0];
  return mod64FromTwoULongs( digit1, digit0,
                                     divisor );
  }

for( Uint32 count = 0; count < index; count++ )
  scratch[count] = D[count];

Uint32 where = index;
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
*/
