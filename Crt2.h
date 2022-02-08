// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "Crt.h"
#include "CrtMath.h"
#include "MultInv.h"
#include "GoodX.h"
#include "RangeC.h"
#include "QuadRes.h"




class Crt2
  {
  private:
  Int32 testForCopy = 123;

  // If last is too small then toInteger()
  // will come out too small.
  static const Int32 last =
                   ProjConst::crtDigitArraySize;

  Int32* digitAr;
  Int32 length = 0;

  inline void setD( Int32 setTo, Int32 index )
    {
    // RangeC::test( index, 0, last - 1,
      //      "Crt2.setD index range." );

    digitAr[index] = setTo;
    }

  inline Int32 getTestAccum( const Int32 prime,
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

  inline bool incNextVal( const Int32 where,
                       const Int32 prime,
                       const Int32 accum,
                       const Int32 accumByte,
                       const Int32 prodByte,
                       const GoodX& goodX,
                       const CrtMath& crtMath )
    {
    // digitAr[where] starts at an unknown value.

    const Int32 crtDigit = crtMath.getCrtDigit(
                                  where, where );

    const Int32 baseByte = crtMath.
                            getBaseByte( where );

    // This has to be very optimized.
    for( Int32 count = 0; count < prime; count++ )
      {
      digitAr[where]++;
      Int32 digit = digitAr[where];

      if( digit >= prime )
        return false;

      Int32 test = getTestAccum( prime,
                                 accum,
                                 crtDigit,
                                 digit );

      if( goodX.getVal( where, test ))
        {
        // accumByte is up to row - 1.
        Int32 testBits = baseByte * digit;
        testBits += accumByte;
        testBits = testBits * testBits;
        testBits += prodByte;
        testBits = testBits & 0xFF;
        if( QuadRes::bytesQR( testBits ))
          return true;

        }
      }

    return false;
    }

  public:
  Crt2( void );
  Crt2( const Crt2& in );
  ~Crt2( void );
  inline void setToZero()
    {
    length = 0;
    digitAr[0] = 0;
    }

  inline void setToOne()
    {
    length = 0;
    digitAr[0] = 1;
    }

  inline void setTo3( void )
    {
    length = 1;
    digitAr[0] = 1;  // 1
    digitAr[1] = 1;  // 2
    }

  inline bool isZero()
    {
    if( length != 0 )
      return false;

    if( digitAr[0] != 0 )
      return false;

    return true;
    }

  inline bool isOne()
    {
    if( length != 0 )
      return false;

    if( digitAr[0] != 1 )
      return false;

    return true;
    }

  inline Int32 digitAtTop()
    {
    return digitAr[length];
    }

  void copy( const Crt2& toCopy );
  bool isEqual( const Crt2& toCheck ) const;

  inline Int32 getD( Int32 index ) const
    {
    // RangeC::test( index, 0, last - 1,
       //    "Crt2.getD index range." );

    return digitAr[index];
    }

  inline Int32 getLength( void ) const
    {
    return length;
    }

  void toInteger( const CrtMath& crtMath,
                  Integer& toSet,
                  IntegerMath& intMath ) const;

  void setFromCrt( const Crt& from,
                   // Integer& accum,
                   const CrtMath& crtMath,
                   const SPrimes& sPrimes,
                   // IntegerMath& intMath
                   const MultInv& multInv
                   );

  void setFromCrtV1( const Crt& from,
                     Integer& accum,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     IntegerMath& intMath );

  void setFromCrtV2( const Crt& from,
                     Integer& accum,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     IntegerMath& intMath );

  void setFromCrtV3( const Crt& from,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes );

  void setFromCrtV4( const Crt& from,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     const MultInv& multInv );

  void setFromCrtV5( const Crt& from,
                     const CrtMath& crtMath,
                     const SPrimes& sPrimes,
                     const MultInv& multInv );

  void setCrt( Crt& toSet,
               const CrtMath& crtMath,
               const SPrimes& sPrimes );

  bool setInvCrt( Crt2& prime2Crt2,
                  const Int32 maxLen,
                  const Crt& prod,
                  const SPrimes& sPrimes,
                  const MultInv& multInv,
                  const CrtMath& crtMath );

  bool incAt( const SPrimes& sPrimes,
              const Int32 where );

  void revInc1( const SPrimes& sPrimes );
  void revInc2( const Int32 prodByte,
                const SPrimes& sPrimes,
                const GoodX& goodX,
                const CrtMath& crtMath );

  inline Int32 getAccum( const Int32 row,
                   const Int32 col,
                   const Int32 prime,
                   const CrtMath& crtMath ) const
    {
    Int32 top = row;
    if( top > length )
      top = length;

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

  bool setInvDigit( const Int32 where,
                    const Int32 prime,
                    const Int32 fromDigit,
                    const Int32 maxLen,
                    const CrtMath& crtMath,
                    const MultInv& multInv );

  Str toStr( const CrtMath& crtMath,
             IntegerMath& intMath );

  void resetUpward( const SPrimes& sPrimes,
                    const GoodX& goodX,
                    const CrtMath& crtMath );

  bool isGoodXAt( const Int32 where,
                  const GoodX& goodX,
                  const CrtMath& crtMath,
                  const SPrimes& sPrimes ) const;

  Int32 isGoodX( const Int32 start,
                 const GoodX& goodX,
                 const CrtMath& crtMath,
                 const SPrimes& sPrimes ) const;

  };
