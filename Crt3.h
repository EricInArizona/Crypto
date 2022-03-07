// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/RangeC.h"

#include "ProjConst.h"
#include "SPrimes.h"
#include "CrtMath.h"
#include "MultInv.h"
#include "QuadRes.h"


// Version 3 of the CRT numbers.


// A lot of these things could be very fast if
// they are done on a GPU.  A lot of things
// could be done independently for each Crt digit
// on a GPU.


class Crt3
  {
  private:
  Int32 testForCopy = 123;

  // If last is too small then toInteger()
  // will come out too small.
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32* crtDigitAr;
  Int32* digitAr;
  Int32 index = 0;

  inline static Int32 getTestAccum( const Int32 prime,
                         const Int32 accum,
                         const Int32 crtDigit,
                         const Int32 digit )
    {
    Int32 test = crtDigit;
    test = test * digit;
    test  += accum;
    test = test % prime;
    return test;
    }

  public:
  Crt3( void );
  Crt3( const Crt3& in );
  ~Crt3( void );

  inline void setToZero()
    {
    index = 0;
    digitAr[0] = 0;
    }

  inline void setToOne()
    {
    index = 0;
    digitAr[0] = 1;
    }

  inline Int32 getAccumByte( const Int32 row,
                             const CrtMath& crtMath ) const

    {
    // It is either zero or one.
    Int32 result = digitAr[0];

    for( Int32 count = 1; count <= row; count++ )
      {
      Int32 accumB = crtMath.getBaseByte( count );
      accumB = accumB * digitAr[count];
      result += accumB;
      result = result & 0xFF;
      }

    return result;
    }


  inline bool isZero() const
    {
    if( index != 0 )
      return false;

    if( digitAr[0] != 0 )
      return false;

    return true;
    }

  inline bool isOne() const
    {
    if( index != 0 )
      return false;

    if( digitAr[0] != 1 )
      return false;

    return true;
    }

  inline Int32 digitAtTop() const
    {
    return digitAr[index];
    }


  void copy( const Crt3& toCopy );
  void copyToCrtBuf( CrtBuf& copyTo );

  bool isEqual( const Crt3& toCheck ) const;

  inline Int32 getD( Int32 where ) const
    {
    RangeC::test2( where, 0, last - 1,
                   "Crt3.getD where range." );

    return digitAr[where];
    }

  inline Int32 getCrtD( Int32 where ) const
    {
    RangeC::test2( where, 0, last - 1,
                   "Crt3.getD where range." );

    return crtDigitAr[where];
    }

  inline void setD( Int32 setTo, Int32 where )
    {
    RangeC::test2( where, 0, last - 1,
                  "Crt2.setD where range." );

    digitAr[where] = setTo;
    }

  inline void setCrtD( Int32 setTo, Int32 where )
    {
    RangeC::test2( where, 0, last - 1,
                  "Crt2.setD where range." );

    crtDigitAr[where] = setTo;
    }


  inline Int32 getIndex( void ) const
    {
    return index;
    }

  inline void setIndex( Int32 setTo )
    {
    RangeC::test2( setTo, 0, last - 1,
                "Crt2.setIndex setTo range." );

    index = setTo;
    }

  void toInteger( const CrtMath& crtMath,
                  Integer& toSet,
                  IntegerMath& intMath ) const;

  void setCrt( const CrtMath& crtMath,
               const SPrimes& sPrimes );

  void setFromCrt( const CrtMath& crtMath,
                   const SPrimes& sPrimes,
                   const MultInv& multInv );

  void setFromCrtV5( const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     const MultInv& multInv );


/*
  bool setInvCrt( Crt3& prime2Crt3,
                  const Int32 maxLen,
                  const Crt3& prod,
                  const SPrimes& sPrimes,
                  const MultInv& multInv,
                  const CrtMath& crtMath );
*/


  // bool incAt( const SPrimes& sPrimes,
    //           const Int32 where );


  inline Int32 getAccum( const Int32 row,
                   const Int32 col,
                   const Int32 prime,
                   const CrtMath& crtMath ) const
    {
    Int32 top = row;
    if( top > index )
      top = index;

    // The crtDigit is all ones at index 0.
    // So it would be this times 1.
    // This is either one or zero.
    Int32 result = digitAr[0];

    for( Int32 count = 1; count <= top; count++ )
      {
      Int32 accum = crtMath.getCrtDigit(
                                   count, col );

      accum = accum * digitAr[count];
      result += accum;
      result = result % prime;
      }

    return result;
    }

/*
  bool setInvDigit( const Int32 where,
                    const Int32 prime,
                    const Int32 fromDigit,
                    const Int32 maxLen,
                    const CrtMath& crtMath,
                    const MultInv& multInv );
*/


  Str toStr( const CrtMath& crtMath,
             IntegerMath& intMath );


/*
  bool isGoodXAt( const Int32 where,
                  const GoodX& goodX,
                  const CrtMath& crtMath,
                  const SPrimes& sPrimes ) const;

  Int32 isGoodX( const Int32 start,
                 const GoodX& goodX,
                 const CrtMath& crtMath,
                 const SPrimes& sPrimes ) const;
*/


/*
  void add( const Crt& toAdd,
            const SPrimes& sPrimes );
  void subtract( const Crt& toSub,
                 const SPrimes& sPrimes );
  void decrement( const SPrimes& sPrimes );
  void subtractInt( const Int32 toSub,
                     const SPrimes& sPrimes );
  void multiply( const Crt& toMul,
                 const SPrimes& sPrimes );

*/


  void setFromInteger( const Integer& setFrom,
                       IntegerMath& intMath,
                       const SPrimes& sPrimes,
                       const MultInv& multInv,
                       const CrtMath& crtMath );


/*
  void setFromInt( const Int32 setFrom,
                    const SPrimes& sPrimes );
*/


  };
