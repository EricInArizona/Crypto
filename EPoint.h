// Copyright Eric Chauvin, 2021.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
// #include "FileIO.h"


// This is for the arithmetic for points on
// an elliptic curve.  Add, subtract, multiply
// and divide points on a curve.  If the points
// are on the curve, then doing these operations
// will result in another point on the curve.


class EPoint
  {
  private:
  Int32 testForCopy = 123;
  bool isInfinite = false;
  Integer X;
  Integer Y;

  public:
  EPoint( void );
  EPoint( const EPoint& in );
  EPoint( Integer& setX, Integer& setY );
  EPoint( EPoint& in );

  // The curve used in Bitcoin: y^2 = x^3 + 7
  static const Uint32 coefA = 0;
  static const Uint32 coefB = 7;

  inline bool getIsInfinite( void )
    {
    return isInfinite;
    }

  inline void setIsInfinite( bool setTo )
    {
    isInfinite = setTo;
    }

  void copy( EPoint& p );
  bool isOnCurve( Integer& modulus,
              Mod& mod, IntegerMath& intMath );
  bool isEqual( EPoint& in );
  bool isConjugate( EPoint& p,
                    Integer& modulus,
                    Mod& mod,
                    IntegerMath& intMath );
  void add( EPoint& p, EPoint& q,
            Integer& modulus,
            Mod& mod,
            IntegerMath& intMath  );
  void doubleP( EPoint& p,
                Integer& modulus,
                Mod& mod,
                IntegerMath& intMath );
  void repeatDoubleP( Integer& twoPower,
                      EPoint p,
                      Integer& modulus,
                      Mod& mod,
                      IntegerMath& intMath );
  void repeatDoublePByAdd( EPoint& p,
                         Integer& twoPower,
                         Integer& modulus,
                         Mod& mod,
                         IntegerMath& intMath );

  };
