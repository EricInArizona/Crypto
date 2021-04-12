// Copyright Eric Chauvin 2021.



#ifndef ECMarkers_H
#define ECMarkers_H


// Basic Multilingual Plane
// C0 Controls and Basic Latin (Basic Latin)
//                                 (0000 007F)
// C1 Controls and Latin-1 Supplement (0080 00FF)
// Latin Extended-A (0100 017F)
// Latin Extended-B (0180 024F)
// IPA Extensions (0250 02AF)
// Spacing Modifier Letters (02B0 02FF)
// Combining Diacritical Marks (0300 036F)
// General Punctuation (2000 206F)
// Superscripts and Subscripts (2070 209F)
// Currency Symbols (20A0 20CF)
// Combining Diacritical Marks for Symbols
//                                (20D0 20FF)
// Letterlike Symbols (2100 214F)
// Number Forms (2150 218F)
// Arrows (2190 21FF)
// Mathematical Operators (2200 22FF)
// Box Drawing (2500 257F)
// Geometric Shapes (25A0 25FF)
// Miscellaneous Symbols (2600 26FF)
// Dingbats (2700 27BF)
// Miscellaneous Symbols and Arrows (2B00 2BFF)


#include "BasicTypes.h"

class Markers
  {
  public:
  static const Uint16 Begin = 0x2203; // 0x2700;



  inline static bool isMarker( Uint16 testChar )
    {
    // Reserve these symbols for markers.
    // Miscellaneous Symbols (0x2600 to 0x26FF)
    // Dingbats (0x2700 to 0x27BF)
    // Miscellaneous Symbols and Arrows (0x2B00 to 0x2BFF)

    if( (testChar >= 0x2600) &&
                           (testChar <= 0x2BFF))
      return true;

    return false;
    }


/*
  public static StrA removeAllMarkers( StrA in )
    {
    if( in == null )
      return StrA.Empty;

    final int max = in.length();
    if( max == 0 )
      return StrA.Empty;

    StrABld sBuilder = new StrABld( in.length());
    for( int count = 0; count < max; count++ )
      {
      char testChar = in.charAt( count );
      if( isMarker( testChar ))
        continue;

      sBuilder.appendChar( testChar );
      }

    return sBuilder.toStrA();
    }
*/


/*
  public static int countMarkers( StrA in )
    {
    if( in == null )
      return 0;

    final int max = in.length();
    if( max == 0 )
      return 0;

    int howMany = 0;
    for( int count = 0; count < max; count++ )
      {
      char testChar = in.charAt( count );
      if( isMarker( testChar ))
        howMany++;

      }

    return howMany;
    }
*/


  };


#endif
