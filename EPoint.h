// Copyright Eric Chauvin, 2021.



#pragma once


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"
// #include "FileIO.h"


// A point on an elliptic curve.


class EPoint
  {
  private:
  bool infin = false; // Infinite
  Integer X;
  Integer Y;

  public:
  EPoint( void );
  EPoint( const EPoint& in );
  EPoint( const Integer& setX,
          const Integer& setY );

  // Domain parameters: (p, a, b, G, n, h )
  // The A and B coeffients define the curve.
  // The curve used in Bitcoin: y^2 = x^3 + 7
  static const Uint32 coefA = 1;
  static const Uint32 coefB = 7;

  inline bool getInfin( void ) const
    {
    return infin;
    }

  inline void setInfin( bool setTo )
    {
    infin = setTo;
    }

  void copy( const EPoint& p );
  bool isEqual( const EPoint& in ) const;
  bool isConjugate( const EPoint& p,
                    const Integer& modulus,
                    Mod& mod,
                    IntegerMath& intMath ) const;
  bool isOnCurve( const Integer& modulus,
              Mod& mod, IntegerMath& intMath );
  void add( const EPoint& p, const EPoint& q,
            const Integer& modulus,
            Mod& mod,
            IntegerMath& intMath  );
  void doubleP( const EPoint& p,
                const Integer& modulus,
                Mod& mod,
                IntegerMath& intMath );

  };
