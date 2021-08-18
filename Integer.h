// Copyright Eric Chauvin, 2021.



#pragma once



#include "BasicTypes.h"
#include "Str.h"
#include "Uint8Array.h"



class Integer
  {
  public:
  // digitArraySize = 100 is 3,200 bits.
  // If RSA::PrimeIndex = 15 the size is 16,
  // so then N, the modulus, has a size of
  //about 32.  Squaring N makes it have an
  // index of about 64.  So about 4 times
  // the size of the primes.
  // With a PrimeIndex of 15, a
  // digitArraySize of 66 overflowed. But not
  // at 67.  16 * 4 = 64.
  // NumbSys is not exact.  It's a little
  // bigger than the modulus.

  static const Uint32 digitArraySize = 515;

  // This would be about 515 times 8 bytes for
  // the size on the stack.  Over 4,000 bytes.
  // See the /STACK option in BuildProj.bat

  private:
  Int32 testforCopy = 123;
  bool isNegative = false;
  Uint32 index = 0;

  // It is Uint64 to hold multiplied values.
  // I want a fixed array that gets pushed on
  // to the stack.  In other words there is
  // no memory allocation that gets done when
  // an Integer is created other than to move
  // the stack pointer.
  Uint64 D[digitArraySize] = { 0,1,2 };
  // Uint64* D;

/*
  void setOneDValueFromChar( Uint64 toSet,
                Uint32 position, Uint32 offset );
  char getOneCharFromDValue(
                Uint32 position, Uint32 offset );
  void setOneDValueFromByte( Uint64 toSet,
                             Uint32 atIndex,
                             Uint32 offset );
  char getOneByteFromDValue(
                  Uint32 atIndex, Uint32 offset );

*/

  public:
  Integer( void );
  Integer( const Integer& obj );
  // ~Integer();

  inline void setToZero( void )
    {
    isNegative = false;
    index = 0;
    D[0] = 0;
    }

  inline void setToOne( void )
    {
    isNegative = false;
    index = 0;
    D[0] = 1;
    }


  inline bool isZero( void )
    {
    if( (index == 0) && (D[0] == 0) )
      return true;

    return false;
    }

  inline bool isOne( void )
    {
    if( isNegative )
      return false;

    if( (index == 0) && (D[0] == 1) )
      return true;

    return false;
    }

  inline bool getIsNegative( void )
    {
    return isNegative;
    }

  inline void setIsNegative( bool setTo )
    {
    isNegative = setTo;
    }

  inline Uint32 getIndex( void )
    {
    return index;
    }

  inline void setIndex( Uint32 where )
    {
    if( where >= digitArraySize )
      throw "setIndex() index out of bounds.";

    index = where;
    }


  inline Uint64 getD( Uint32 where )
    {
    if( where >= digitArraySize )
      throw "getD() index out of bounds.";

    return D[where];
    }

  inline void setD( Uint32 where, Uint64 toSet )
    {
    // I want to be able to use toSet values
    // that might be a full 64 bits long.
    // See cleanUp().

    if( where >= digitArraySize )
      throw "setD() index out of bounds.";

    D[where] = toSet;
    }

  void cleanUp( void );
  void incrementIndex( void );
  void setToMaxValue( void );
  inline void setFromUInt( Uint32 toSet )
    {
    isNegative = false;
    D[0] = toSet;
    index = 0;
    }

  void setFromULong( Uint64 toSet );
  void copy( Integer& copyFrom );
  // void copyFromP( const Integer* copyFrom );
  void copyUpTo( const Integer& copyFrom,
                                 Uint32 where );
  bool isEqualToULong( Uint64 toTest );
  bool isEqual( Integer& x );
  bool isULong( void );
  Uint64 getAsULong( void );
  bool paramIsGreater( Integer& x );
  bool paramIsGreaterOrEq( Integer& x );
  void increment( void );
  void addULong( Uint64 toAdd );
  void add( Integer& toAdd );
  void square0( void );
  void square1( void );
  void square2( void );
  void shiftLeft( Uint32 shiftBy );
  void shiftRight( Uint32 shiftBy );
  void setDigitAndClear( Uint32 where,
                                  Uint64 toSet );
  bool makeRandomOdd( Uint32 setToIndex );

/*
  bool setFromAsciiStr( Str& in );
  Str getAsciiStr( void );
  void setFromBigEndianByteArray(
                              Uint8Array& U8Ar );
  void getBigEndianByteArray(
                             Uint8Array& toGet );
*/

  };
