// Copyright Eric Chauvin 2021.


#include "Euclid.h"
#include "Division.h"


void Euclid::greatestComDiv( Integer& X,
                             Integer& Y,
                             Integer& gcd,
                             IntegerMath& intMath )
{
// This is the basic Euclidean Algorithm
// for GCD.

if( X.isZero())
  throw "Doing GCD with a param that is zero.";

if( Y.isZero())
  throw "Doing GCD with a param that is zero.";

if( X.isEqual( Y ))
  {
  gcd.copy( X );
  return;
  }

Integer gcdX;
Integer gcdY;


// Don't change the original numbers that came
// in as parameters.
if( X.paramIsGreater( Y ))
  {
  gcdX.copy( Y );
  gcdY.copy( X );
  }
else
  {
  gcdX.copy( X );
  gcdY.copy( Y );
  }

Integer quotient;
Integer remainder;

while( true )
  {
  Division::divide( gcdX, gcdY, quotient,
                    remainder, intMath );
  if( remainder.isZero())
    {
    gcd.copy( gcdY ); // It's the smaller one.
    // It can't return from this loop until
    // the remainder is zero.
    return;
    }

  gcdX.copy( gcdY );
  gcdY.copy( remainder );
  }
}




// Reciprocity?
// They have a kind of reciprical relationship.
// This is how they relate to each other.
// "x is the modular multiplicative inverse
// of a modulo b, and y is the modular
// multiplicative inverse of b modulo a."


/*
The extended Euclidean algorithm gives the
multiplicative inverse.

Euclid class.
  internal bool MultiplicativeInverse( Integer X, Integer Modulus, Integer MultInverse, BackgroundWorker Worker )
    {
    // This is the extended Euclidean Algorithm.
    // A*X + B*Y = Gcd
    // A*X + B*Y = 1 If there's a multiplicative inverse.
    // A*X = 1 - B*Y so A is the multiplicative inverse of X mod Y.
    if( X.IsZero())
      throw( new Exception( "Doing Multiplicative Inverse with a parameter that is zero." ));

    if( Modulus.IsZero())
      throw( new Exception( "Doing Multiplicative Inverse with a parameter that is zero." ));

    // This happens sometimes:
    // if( Modulus.ParamIsGreaterOrEq( X ))
      // throw( new Exception( "Modulus.ParamIsGreaterOrEq( X ) for Euclid." ));

    // Worker.ReportProgress( 0, " " );
    // Worker.ReportProgress( 0, " " );
    // Worker.ReportProgress( 0, "Top of mod inverse." );
    // U is the old part to keep.
    U0.SetToZero();
    U1.SetToOne();
    U2.Copy( Modulus ); // Don't change the original numbers that came in as parameters.
    // V is the new part.
    V0.SetToOne();
    V1.SetToZero();
    V2.Copy( X );
    T0.SetToZero();
    T1.SetToZero();
    T2.SetToZero();
    Quotient.SetToZero();
    // while( not forever if there's a problem )
    for( int Count = 0; Count < 10000; Count++ )
      {
      if( U2.IsNegative )
        throw( new Exception( "U2 was negative." ));

      if( V2.IsNegative )
        throw( new Exception( "V2 was negative." ));

      Divider.Divide( U2, V2, Quotient, Remainder );
      if( Remainder.IsZero())
        {
        Worker.ReportProgress( 0, "Remainder is zero. No multiplicative-inverse." );
        return false;
        }

      TempEuclid1.Copy( U0 );
      TempEuclid2.Copy( V0 );
      Multiply( TempEuclid2, Quotient );
      Subtract( TempEuclid1, TempEuclid2 );
      T0.Copy( TempEuclid1 );
      TempEuclid1.Copy( U1 );
      TempEuclid2.Copy( V1 );
      Multiply( TempEuclid2, Quotient );
      Subtract( TempEuclid1, TempEuclid2 );
      T1.Copy( TempEuclid1 );
      TempEuclid1.Copy( U2 );
      TempEuclid2.Copy( V2 );
      Multiply( TempEuclid2, Quotient );
      Subtract( TempEuclid1, TempEuclid2 );
      T2.Copy( TempEuclid1 );
      U0.Copy( V0 );
      U1.Copy( V1 );
      U2.Copy( V2 );
      V0.Copy( T0 );
      V1.Copy( T1 );
      V2.Copy( T2 );
      if( Remainder.IsOne())
        {
        // Worker.ReportProgress( 0, " " );
        // Worker.ReportProgress( 0, "Remainder is 1. There is a multiplicative-inverse." );
        break;
        }
      }

    MultInverse.Copy( T0 );
    if( MultInverse.IsNegative )
      {
      Add( MultInverse, Modulus );
      }

    // Worker.ReportProgress( 0, "MultInverse: " + ToString10( MultInverse ));
    TestForModInverse1.Copy( MultInverse );
    TestForModInverse2.Copy( X );
    Multiply( TestForModInverse1, TestForModInverse2 );
    Divider.Divide( TestForModInverse1, Modulus, Quotient, Remainder );
    if( !Remainder.IsOne())  // By the definition of Multiplicative inverse:
      throw( new Exception( "MultInverse is wrong: " + ToString10( Remainder )));

    // Worker.ReportProgress( 0, "MultInverse is the right number: " + ToString10( MultInverse ));
    return true;
    }

*/




/*

  internal bool IntegerMath::
          FindMultiplicativeInverseSmall( Integer ToFind, Integer KnownNumber, Integer Modulus, BackgroundWorker Worker )
    {
    // This method is for: KnownNumber * ToFind = 1
    // mod Modulus
    // An example:
    // PublicKeyExponent * X = 1 mod PhiN.
    // PublicKeyExponent * X = 1 mod (P - 1)(Q - 1).
    // This means that
    // (PublicKeyExponent * X) = (Y * PhiN) + 1
    // X is less than PhiN.
    // So Y is less than PublicKExponent.
    // Y can't be zero.
    // If this equation can be solved then it can be solved modulo
    // any number.  So it has to be solvable mod PublicKExponent.
    // See: Hasse Principle.
    // This also depends on the idea that the KnownNumber is prime and
    // that there is one unique modular inverse.
    // if( !KnownNumber-is-a-prime )
    //    then it won't work.
    if( !KnownNumber.IsULong())
      throw( new Exception( "FindMultiplicativeInverseSmall() was called with too big of a KnownNumber." ));

    ulong KnownNumberULong  = KnownNumber.GetAsULong();
    //                       65537
    if( KnownNumberULong > 1000000 )
      throw( new Exception( "KnownNumberULong > 1000000. FindMultiplicativeInverseSmall() was called with too big of an exponent." ));

    // (Y * PhiN) + 1 mod PubKExponent has to be zero if Y is a solution.
    ulong ModulusModKnown = Divider.GetMod32( Modulus, KnownNumberULong );
    Worker.ReportProgress( 0, "ModulusModExponent: " + ModulusModKnown.ToString( "N0" ));
    if( Worker.CancellationPending )
      return false;

    // Y can't be zero.
    // The exponent is a small number like 65537.
    for( uint Y = 1; Y < (uint)KnownNumberULong; Y++ )
      {
      ulong X = (ulong)Y * ModulusModKnown;
      X++; // Add 1 to it for (Y * PhiN) + 1.
      X = X % KnownNumberULong;
      if( X == 0 )
        {
        if( Worker.CancellationPending )
          return false;

        // What is PhiN mod 65537?
        // That gives me Y.
        // The private key exponent is X*65537 + ModPart
        // The CipherText raised to that is the PlainText.
        // P + zN = C^(X*65537 + ModPart)
        // P + zN = C^(X*65537)(C^ModPart)
        // P + zN = ((C^65537)^X)(C^ModPart)
        Worker.ReportProgress( 0, "Found Y at: " + Y.ToString( "N0" ));
        ToFind.Copy( Modulus );
        MultiplyULong( ToFind, Y );
        ToFind.AddULong( 1 );
        Divider.Divide( ToFind, KnownNumber, Quotient, Remainder );
        if( !Remainder.IsZero())
          throw( new Exception( "This can't happen. !Remainder.IsZero()" ));

        ToFind.Copy( Quotient );
        // Worker.ReportProgress( 0, "ToFind: " + ToString10( ToFind ));
        break;
        }
      }

    if( Worker.CancellationPending )
      return false;

    TestForModInverse1.Copy( ToFind );
    MultiplyULong( TestForModInverse1, KnownNumberULong );
    Divider.Divide( TestForModInverse1, Modulus, Quotient, Remainder );
    if( !Remainder.IsOne())
      {
      // The definition is that it's congruent to 1 mod the modulus,
      // so this has to be 1.
      // I've only seen this happen once.  Were the primes P and Q not
      // really primes?
      throw( new Exception( "Remainder has to be 1: " + ToString10( Remainder ) ));
      }

    return true;
    }

*/
