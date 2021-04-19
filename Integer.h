// Copyright Eric Chauvin, 2021.



#ifndef ECInteger_H
#define ECInteger_H



#include "BasicTypes.h"
#include "Str.h"
#include "Uint8Array.h"



class Integer
  {
  private:

  // This many 32 bit integers.
  // 100 is 3,200 bits.
  static const Uint32 digitArraySize = 200;
  bool isNegative = false;
  Uint32 index = 0;

  // I want this to be a fixed size that can be
  // pushed on the stack.  The only memory
  // allocation that is done is to move the
  // stack pointer.

  // It is Uint64 to hold multiplied values.
  Uint64 D[digitArraySize] =
                  { 0,1,2,3,4,5,6,7,8,9, // 10
                    0,1,2,3,4,5,6,7,8,9, // 20
                    0,1,2,3,4,5,6,7,8,9, // 30
                    0,1,2,3,4,5,6,7,8,9, // 40
                    0,1,2,3,4,5,6,7,8,9, // 50
                    0,1,2,3,4,5,6,7,8,9, // 60
                    0,1,2,3,4,5,6,7,8,9, // 70
                    0,1,2,3,4,5,6,7,8,9, // 80
                    0,1,2,3,4,5,6,7,8,9, // 90
                    0,1,2,3,4,5,6,7,8,9, // 100
                    // 100
                    0,1,2,3,4,5,6,7,8,9, // 10
                    0,1,2,3,4,5,6,7,8,9, // 20
                    0,1,2,3,4,5,6,7,8,9, // 30
                    0,1,2,3,4,5,6,7,8,9, // 40
                    0,1,2,3,4,5,6,7,8,9, // 50
                    0,1,2,3,4,5,6,7,8,9, // 60
                    0,1,2,3,4,5,6,7,8,9, // 70
                    0,1,2,3,4,5,6,7,8,9, // 80
                    0,1,2,3,4,5,6,7,8,9, // 90
                    0,1,2,3,4,5,6,7,8,9 };// 100
                       // 200

  Uint64 scratch[digitArraySize] =
                  { 0,1,2,3,4,5,6,7,8,9, // 10
                    0,1,2,3,4,5,6,7,8,9, // 20
                    0,1,2,3,4,5,6,7,8,9, // 30
                    0,1,2,3,4,5,6,7,8,9, // 40
                    0,1,2,3,4,5,6,7,8,9, // 50
                    0,1,2,3,4,5,6,7,8,9, // 60
                    0,1,2,3,4,5,6,7,8,9, // 70
                    0,1,2,3,4,5,6,7,8,9, // 80
                    0,1,2,3,4,5,6,7,8,9, // 90
                    0,1,2,3,4,5,6,7,8,9, // 100
                    // 100
                    0,1,2,3,4,5,6,7,8,9, // 10
                    0,1,2,3,4,5,6,7,8,9, // 20
                    0,1,2,3,4,5,6,7,8,9, // 30
                    0,1,2,3,4,5,6,7,8,9, // 40
                    0,1,2,3,4,5,6,7,8,9, // 50
                    0,1,2,3,4,5,6,7,8,9, // 60
                    0,1,2,3,4,5,6,7,8,9, // 70
                    0,1,2,3,4,5,6,7,8,9, // 80
                    0,1,2,3,4,5,6,7,8,9, // 90
                    0,1,2,3,4,5,6,7,8,9 };// 100
                       // 200

  void setOneDValueFromChar( Uint64 toSet,
                Uint32 position, Uint32 offset );
  char getOneCharFromDValue(
                Uint32 position, Uint32 offset );
  void setOneDValueFromByte( Uint64 toSet,
                  Uint32 setIndex, Uint32 offset );
  char getOneByteFromDValue(
                  Uint32 atIndex, Uint32 offset );


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

  inline Uint32 getIndex( void )
    {
    return index;
    }

  inline void setIndex( Uint32 where )
    {
    index = where;
    }

  inline Uint64 getD( Uint32 where )
    {
    // if( where >= digitArraySize )

    return D[where];
    }

  inline void setD( Uint32 where, Uint32 toSet )
    {
    // if( where >= digitArraySize )

    D[where] = toSet;
    }

  void incrementIndex( void );
  void setToMaxValue( void );
  inline void setFromUInt( Uint32 toSet )
    {
    isNegative = false;
    D[0] = toSet;
    index = 0;
    }

  void setFromULong( Uint64 toSet );
  void copy( const Integer& copyFrom );
  void copyFromP( const Integer* copyFrom );
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
  bool makeRandomOdd( Uint32 setToIndex,
                             Uint8 randBytes[],
                             Uint32 howMany );
  bool setFromAsciiStr( Str& in );
  Str getAsciiStr( void );
  // void setFromBigEndianByteArray(
     //                         Uint8 inArray[],
     //                         Uint32 howMany );
  void setFromBigEndianByteArray(
                              Uint8Array& U8Ar );
  void getBigEndianByteArray(
                             Uint8Array& toGet );
  static Uint64 mod64FromTwoULongs( Uint64 P1,
                                 Uint64 P0,
                                 Uint64 divisor );
  Uint64 getMod32( Uint64 divisor );
  Uint64 getMod64( Uint64 divisor );



  };


#endif