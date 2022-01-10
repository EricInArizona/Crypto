// Copyright Eric Chauvin 2021 - 2022.



#include "QuadRes.h"


QuadRes::QuadRes( void )
{
bArrays = new BoolArray[last];
}


QuadRes::QuadRes( const QuadRes& in )
{
bArrays = new BoolArray[last];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for QuadRes.";
}


QuadRes::~QuadRes( void )
{
delete[] bArrays;
}



void QuadRes::init( SPrimes& sPrimes )
{
for( Uint32 count = 0; count < last; count++ )
  {
  Uint32 prime = sPrimes.getPrimeAt( count );
  bArrays[count].setSize( prime );


  bArrays[count].setVal( 0, true );

  for( Uint32 countF = 1; countF < prime;
                                    countF++ )
    {
    bArrays[count].setVal( countF, false );
    }

  for( Uint32 countP = 1; countP < prime;
                                    countP++ )
    {
    Uint32 test = countP * countP;
    test = test % prime;

    // The one at test is a quadratic residue.
    bArrays[count].setVal( test, true );
    }
  }
}






// isSmallQuadResidue().
bool QuadRes::isSmallQR( const Uint32 number )
{
// For mod 2:
// 1 * 1 = 1 % 2 = 1
// 0 * 0 = 0 % 2 = 0
Uint32 test = number % 3; // 0, 1, 1, 0
if( test == 2 )
  return false;

test = number % 5;
if( (test == 2) || (test == 3))
                             // 0, 1, 4, 4, 1, 0
  return false;

test = number % 7;
if( !((test == 0) ||
      (test == 1) ||
      (test == 4) ||
      (test == 2)) )
  return false;

test = number % 11;
if( !((test == 0) ||
      (test == 1) ||
      (test == 4) ||
      (test == 9) ||
      (test == 5) ||
      (test == 3)) )
  return false;

test = number % 13;
if( !((test == 0) ||
      (test == 1) ||
      (test == 4) ||
      (test == 9) ||
      (test == 3) ||
      (test == 12) ||
      (test == 10)) )
  return false;

// If it made it this far...
return true;
}



bool QuadRes::isQR17( const Uint32 number )
{
Uint32 test = number % 17;
if( !((test == 0) ||
      (test == 1) ||
      (test == 4) ||
      (test == 9) ||
      (test == 16) ||
      (test == 8) ||
      (test == 2) ||
      (test == 15) ||
      (test == 13)) )
  return false;

return true;
}



bool QuadRes::isQR19( const Uint32 number )
{
Uint32 test = number % 19;
if( !((test == 0) ||
      (test == 1) ||
      (test == 4) ||
      (test == 9) ||
      (test == 16) ||
      (test == 6) ||
      (test == 17) ||
      (test == 11) ||
      (test == 7) ||
      (test == 5)) )
  return false;

return true;
}



bool QuadRes::isQR23( const Uint32 number )
{
Uint32 test = number % 23;
if( !((test == 0) ||
      (test == 1) ||
      (test == 4) ||
      (test == 9) ||
      (test == 16) ||
      (test == 2) ||
      (test == 13) ||
      (test == 3) ||
      (test == 18) ||
      (test == 12) ||
      (test == 8) ||
      (test == 6)) )
  return false;

return true;
}


/*
bool QuadRes::isQR29( const Uint32 number )
{
Uint32 Test = (uint)(Number % 29);
    if( !((Test == 0) ||
          (Test == 1) ||
          (Test == 4) ||
          (Test == 9) ||
          (Test == 16) ||
          (Test == 25) ||
          (Test == 7) ||
          (Test == 20) ||
          (Test == 6) ||
          (Test == 23) ||
          (Test == 13) ||
          (Test == 5) ||
          (Test == 28) ||
          (Test == 24) ||
          (Test == 22)) )
      return false;

    return true;
    }



  internal static bool IsQuadResidue31( ulong Number )
    {
    uint Test = (uint)(Number % 31);
    if( !((Test == 0) ||
          (Test == 1) ||
          (Test == 4) ||
          (Test == 9) ||
          (Test == 16) ||
          (Test == 25) ||
          (Test == 5) ||
          (Test == 18) ||
          (Test == 2) ||
          (Test == 19) ||
          (Test == 7) ||
          (Test == 28) ||
          (Test == 20) ||
          (Test == 14) ||
          (Test == 10) ||
          (Test == 8)))
      return false;

    return true;
    }



  internal static bool IsQuadResidue37( ulong Number )
    {
    uint Test = (uint)(Number % 37);
    if( !((Test == 0) ||
          (Test == 1) ||
          (Test == 4) ||
          (Test == 9) ||
          (Test == 16) ||
          (Test == 25) ||
          (Test == 36) ||
          (Test == 12) ||
          (Test == 27) ||
          (Test == 7) ||
          (Test == 26) ||
          (Test == 10) ||
          (Test == 33) ||
          (Test == 21) ||
          (Test == 11) ||
          (Test == 3) ||
          (Test == 34) ||
          (Test == 30) ||
          (Test == 28)))
      return false;

    return true;
    }
*/



bool QuadRes::bytesQR( const Uint32 test )
{
// Is this number a square mod 2^12?
// (Quadratic residue mod 2^12)
Uint32 firstByte = test;

// Uint32 secondByte = (firstByte & 0x0F00) >> 8;
// The bottom 4 bits can only be 0, 1, 4 or 9
// 0000, 0001, 0100 or 1001
// The bottom 2 bits can only be 00 or 01
firstByte = firstByte & 0x0FF;
switch( firstByte )
  {
  case 0x00: return true;
    // if( (secondByte == 0) ||
    //    (secondByte == 1) ||
    //    (secondByte == 4) ||
    //    (secondByte == 9))
      // return true;
    // else
      // return false;

  case 0x01: return true;
  case 0x04: return true;
  case 0x09: return true;
  case 0x10: return true;
  case 0x11: return true;
  case 0x19: return true;
  case 0x21: return true;
  case 0x24: return true;
  case 0x29: return true;
  case 0x31: return true;
  case 0x39: return true;
  case 0x40: return true;
   // 0x40, 0, 2, 4, 6, 8, 10, 12, 14
  // if( (secondByte & 0x01) == 0x01 )
    // return false;
  // else
    // return true;

  case 0x41: return true;
  case 0x44: return true;
  case 0x49: return true;
  case 0x51: return true;
  case 0x59: return true;
  case 0x61: return true;
  case 0x64: return true;
  case 0x69: return true;
  case 0x71: return true;
  case 0x79: return true;
  case 0x81: return true;
  case 0x84: return true;
  case 0x89: return true;
  case 0x90: return true;
  case 0x91: return true;
  case 0x99: return true;
  case 0xA1: return true;
  case 0xA4: return true;
  case 0xA9: return true;
  case 0xB1: return true;
  case 0xB9: return true;
  case 0xC1: return true;
  case 0xC4: return true;
  case 0xC9: return true;
  case 0xD1: return true;
  case 0xD9: return true;
  case 0xE1: return true;
  case 0xE4: return true;
  case 0xE9: return true;
  case 0xF1: return true;
  case 0xF9: return true;  // 44 out of 256.

  default: return false;
  }
}
