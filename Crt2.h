// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


#include "BasicTypes.h"
#include "ProjConst.h"
#include "SPrimes.h"
#include "Crt.h"
#include "CrtMath.h"
#include "MultInv.h"
#include "GoodX.h"




class Crt2
  {
  private:
  Int32 testForCopy = 123;

  // If last is too small then toInteger()
  // will come out too small.
  static const Uint32 last =
                   ProjConst::crtDigitArraySize;

  Int32* digitAr;
  Uint32 length = 0;

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

  inline Int32 getD( Uint32 index ) const
    {
    // Comment out after testing:
    // if( index >= last )
      // throw "Crt2 GetD Index is too big.";

    return digitAr[index];
    }

  inline void setD( Int32 setTo, Uint32 index )
    {
    // if( index >= last )
      // throw "Crt2 SetD Index is too big.";

    digitAr[index] = setTo;
    }

  inline Uint32 getLength( void ) const
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
                  const Uint32 maxLen,
                  const Crt& prod,
                  const SPrimes& sPrimes,
                  const MultInv& multInv,
                  const CrtMath& crtMath );

  bool increment( const SPrimes& sPrimes );
  bool incAt( const SPrimes& sPrimes,
                         const Uint32 where );

  bool incRev( const SPrimes& sPrimes,
               const Uint32 where,
               const GoodX& goodX,
               const CrtMath& crtMath );

  inline bool incNextVal( const Uint32 where,
                       const Uint32 prime,
                       const Uint32 accum,
                       const GoodX& goodX,
                       const CrtMath& crtMath )
    {
    // This will get the _next_ good value.
    // digitAr[where] starts at an unknown value.

    const Uint32 crtDigit = crtMath.getCrtDigit(
                                  where, where );

    for( Uint32 count = 0; count < prime; count++ )
      {
      digitAr[where]++;

      if( (Uint32)digitAr[where] >= prime )
        return false;

      Uint32 digit = (Uint32)digitAr[where];
      Uint32 test = getTestAccum( prime,
                                  accum,
                                  crtDigit,
                                  digit );

      if( goodX.getVal( where, test ))
        return true;

      }

    // throw "It will never get here.";
    return false;
    }

  inline Uint32 getTestAccum( const Uint32 prime,
                         const Uint32 accum,
                         const Uint32 crtDigit,
                         const Uint32 digit )
    {
    Uint32 test = crtDigit;
    test = test * digit;
    test  += accum;
    test = test % prime;
    return test;
    }

  inline bool incCheckVal( const Uint32 where,
                       const Uint32 prime,
                       const Uint32 accum,
                       const GoodX& goodX,
                       const CrtMath& crtMath )
    {
    const Uint32 crtDigit = crtMath.getCrtDigit(
                                  where, where );

    for( Uint32 count = 0; count < prime; count++ )
      {
      Uint32 digit = (Uint32)digitAr[where];
      Uint32 test = getTestAccum( prime,
                                  accum,
                                  crtDigit,
                                  digit );

      if( goodX.getVal( where, test ))
        return true;

      digitAr[where]++;
      if( (Uint32)digitAr[where] >= prime )
        return false;

      }

    // throw "It will never get here.";
    return false;
    }

  inline Uint32 getAccumD( const Uint32 row,
                           const Uint32 col,
                           const Uint32 prime,
                           const CrtMath& crtMath )
    {
    // It is either zero or one.
    Uint32 result = (Uint32)digitAr[0];

    for( Uint32 count = 1; count <= row; count++ )
      {
      Uint32 accum = crtMath.getCrtDigit( count,
                                          col );
      accum = accum * (Uint32)digitAr[count];
      result += accum;
      result = result % prime;
      }

    return result;
    }

  bool setInvDigit( const Uint32 where,
                    const Uint32 prime,
                    const Uint32 fromDigit,
                    const Uint32 maxLen,
                    const CrtMath& crtMath,
                    const MultInv& multInv );

  void resetUpward( const Uint32 where,
                    const Uint32 max,
                    const SPrimes& sPrimes,
                    const GoodX& goodX,
                    const CrtMath& crtMath );

  };
