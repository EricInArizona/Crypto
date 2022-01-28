// Copyright Eric Chauvin, 2021 - 2022.



#pragma once



#include "BasicTypes.h"
#include "Str.h"
#include "ProjConst.h"
#include "IntBuf.h"
#include "RangeC.h"



class Integer
  {
  public:
  // This would be about 515 times 8 bytes for
  // the size on the stack.  Over 4,000 bytes.
  // See the /STACK option in BuildProj.bat

  private:
  Int32 testforCopy = 123;
  bool negative = false;
  Int32 index = 0;

  // It is Int64 to hold multiplied values.
  // I want a fixed array that gets pushed on
  // to the stack.  In other words there is
  // no memory allocation that gets done when
  // an Integer is created other than to move
  // the stack pointer.
  Int64 D[ProjConst::digitArraySize] = { 0,1,2 };
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
    negative = false;
    index = 0;
    D[0] = 0;
    }

  inline void setToOne( void )
    {
    negative = false;
    index = 0;
    D[0] = 1;
    }


  inline bool isZero( void ) const
    {
    // if( negative )
    // throw ...

    if( (index == 0) && (D[0] == 0) )
      return true;

    return false;
    }

  inline bool isOne( void ) const
    {
    if( negative )
      return false;

    if( (index == 0) && (D[0] == 1) )
      return true;

    return false;
    }

  inline bool isMoreThanInt( const Int32 check )
                                           const
    {
    if( negative )
      return false;

    if( index > 0 )
      return true;

    if( D[0] > check )
      return true;

    return false;
    }

  inline bool getNegative( void ) const
    {
    return negative;
    }

  inline void setNegative( bool setTo )
    {
    negative = setTo;
    }

  inline Int32 getIndex( void ) const
    {
    return index;
    }

  inline void setIndex( Int32 setTo )
    {
    RangeC::test( setTo, 0,
               ProjConst::digitArraySize - 1 );

    index = setTo;
    }


  inline Int64 getD( const Int32 where ) const
    {
    RangeC::test( where, 0,
               ProjConst::digitArraySize - 1 );

    return D[where];
    }

  inline void setD( const Int32 where,
                    const Int64 toSet )
    {
    // I want to be able to use toSet values
    // that might be a full 48 bits long.
    // See cleanUp().

    RangeC::test( where, 0,
               ProjConst::digitArraySize - 1 );

    D[where] = toSet;
    }

  void cleanUp( void );
  void incrementIndex( void );
  void setToMaxValue( void );
  inline void setFromInt( const Int32 toSet )
    {
    negative = false;
    D[0] = toSet;
    index = 0;
    }

  void setFromLong( const Int64 toSet );
  void copy( const Integer& copyFrom );
  void copyUpTo( const Integer& copyFrom,
                 const Int32 where );
  // The const on the end marks this function
  // as not modifying the _this_ object that
  // called it.
  // bool isEqualToInt( const Int32 toTest ) const;
  // bool isEqualToInt64( const Int64 toTest )
  //                                     const;
  bool isEqual( const Integer& x ) const;
  bool isLong( void ) const;
  Int64 getAsLong( void ) const;
  bool paramIsGreater( const Integer& x ) const;
  bool paramIsGreaterOrEq( const Integer& x )
                                          const;
  void increment( void );
  void addLong( const Int64 toAdd );
  void add( const Integer& toAdd );
  void square0( void );
  void square1( void );
  void square2( void );
  void shiftLeft( const Int32 shiftBy );
  void shiftRight( const Int32 shiftBy );
  void setDigitAndClear( const Int32 where,
                            const Int64 toSet );
  bool makeRandomOdd( const Int32 setToIndex );

/*
  bool setFromAsciiStr( Str& in );
  Str getAsciiStr( void );

  do char arrays.
  void setFromBigEndianByteArray(
                              Uint8Array& U8Ar );
  void getBigEndianByteArray(
                             Uint8Array& toGet );
*/

  void copyFromIntBuf( IntBuf& intBuf );
  void copyToIntBuf( IntBuf& intBuf ) const;

  };
