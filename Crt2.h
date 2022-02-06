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

  public:
  Crt2( void );
  Crt2( const Crt2& in );
  ~Crt2( void );
  void setToZero();
  void setToOne();
  bool isZero();
  bool isOne();
  void copy( const Crt2& toCopy );
  bool isEqual( const Crt2& toCheck );

  inline Int32 getD( Int32 index ) const
    {
    RangeC::test( index, 0, last - 1,
            "Crt2.getD index range." );

    return digitAr[index];
    }

  inline void setD( Int32 setTo, Int32 index )
    {
    RangeC::test( index, 0, last - 1,
            "Crt2.setD index range." );

    digitAr[index] = setTo;
    }

  inline Int32 getLength( void ) const
    {
    return length;
    }

  void toInteger( const CrtMath& crtMath,
                  Integer& toSet,
                  IntegerMath& intMath );

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

  bool increment( const SPrimes& sPrimes );
  bool incAt( const SPrimes& sPrimes,
              const Int32 where );

  bool incRev( const SPrimes& sPrimes,
               const Int32 where,
               const GoodX& goodX,
               const CrtMath& crtMath );

  inline bool incNextVal( const Int32 where,
                       const Int32 prime,
                       const Int32 accum,
                       const GoodX& goodX,
                       const CrtMath& crtMath )
    {
    // This will get the _next_ good value.
    // digitAr[where] starts at an unknown value.

    const Int32 crtDigit = crtMath.getCrtDigit(
                                  where, where );

    for( Int32 count = 0; count < prime; count++ )
      {
      digitAr[where]++;

      if( digitAr[where] >= prime )
        return false;

      Int32 digit = digitAr[where];
      Int32 test = getTestAccum( prime,
                                  accum,
                                  crtDigit,
                                  digit );

      if( goodX.getVal( where, test ))
        return true;

      }

    // throw "It will never get here.";
    return false;
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

  inline bool incCheckVal( const Int32 where,
                       const Int32 prime,
                       const Int32 accum,
                       const GoodX& goodX,
                       const CrtMath& crtMath )
    {
    const Int32 crtDigit = crtMath.getCrtDigit(
                                  where, where );

    for( Int32 count = 0; count < prime; count++ )
      {
      Int32 digit = digitAr[where];
      Int32 test = getTestAccum( prime,
                                 accum,
                                 crtDigit,
                                 digit );

      if( goodX.getVal( where, test ))
        return true;

      digitAr[where]++;
      if( digitAr[where] >= prime )
        return false;

      }

    // throw "It will never get here.";
    return false;
    }

  inline Int32 getAccumD( const Int32 row,
                          const Int32 col,
                          const Int32 prime,
                          const CrtMath& crtMath )
    {
    RangeC::test( row, 0, last - 1,
            "Crt2.getAccumD() row range." );

    RangeC::test( col, 0, last - 1,
            "Crt2.getAccumD() col range." );

    // It is either zero or one.
    Int32 result = digitAr[0];

    for( Int32 count = 1; count <= row; count++ )
      {
      Int32 accum = crtMath.getCrtDigit( count,
                                          col );
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

  void resetUpward( const Int32 where,
                    const Int32 max,
                    const SPrimes& sPrimes,
                    const GoodX& goodX,
                    const CrtMath& crtMath );

  };
