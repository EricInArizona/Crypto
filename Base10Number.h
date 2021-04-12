// Copyright Eric Chauvin 2021.



#ifndef ECBase10Number_H
#define ECBase10Number_H


#include "BasicTypes.h"
#include "Str.h"


class Base10Number
  {
  // The number string 123456789 is put in the array of digits
  // like this:
  // D[0] = 9; // Least significant digit.
  // D[1] = 8;
  // D[2] = 7;
  // D[3] = 6;
  // D[4] = 5;
  // D[5] = 4;
  // D[6] = 3;
  // D[7] = 2;
  // D[8] = 1; // Most significant digit.

  private:
  // For 1024 bits it's about 309 decimal digits.
  static const Uint32 digitArraySize =
                                   (310 * 4) + 2;
  Uint32 index = 0;
  Uint16* D;

  public:
  Base10Number( Str& toSet );
  Base10Number( const Base10Number& obj );
  ~Base10Number( void );
  Uint32 getD( Uint32 where );

  inline Uint32 getIndex( void )
    {
    return index;
    }

  Uint16 convertDigit( Uint16 digit );
  void setFromStr( Str& toSet );

  };


#endif
