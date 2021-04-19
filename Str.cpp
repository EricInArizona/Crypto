// Copyright Eric Chauvin 2021.



#include "Str.h"
#include "StIO.h"


Str::Str( const char* pStr )
{
const char* sizePoint = pStr;

arraySize = 0;
for( Uint32 count = 0; count < 10000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    break;

  sizePoint++;
  arraySize++;
  }

cArray = new char[arraySize];
for( Uint32 count = 0; count < arraySize;
                                       count++ )
  {
  char c = *pStr;
  cArray[count] = c;
  pStr++;
  }
}


Str::Str( char ar[], const Uint32 howMany )
{
arraySize = howMany;
cArray = new char[arraySize];
for( Uint32 count = 0; count < arraySize;
                                        count++ )
  cArray[count] = ar[count];

}



// The copy constructor.
Str::Str( const Str& obj )
{
arraySize = obj.arraySize;
cArray = new char[arraySize];
for( Uint32 count = 0; count < arraySize; count++ )
  {
  cArray[count] = obj.cArray[count];
  }

StIO::uPrintf( "Str copy constructor called.\n" );
}



Str::~Str( void )
{
delete[] cArray;
}


char Str::charAt( Uint32 where )
{
if( where >= arraySize )
  throw "In charAt() index out of bounds.";

return cArray[where];
}


void Str::print()
{
if( arraySize == 0 )
  return;

for( Uint32 count = 0; count < arraySize; count++ )
  StIO::putC( cArray[count] );

}


void Str::printLine()
{
if( arraySize == 0 )
  {
  StIO::putC( '\n' );
  return;
  }

for( Uint32 count = 0; count < arraySize; count++ )
  StIO::putC( cArray[count] );

StIO::putC( '\n' );
}



Uint32 Str::charsLength( const char* pStr )
{
const char* sizePoint = pStr;

Uint32 howMany = 0;
for( Uint32 count = 0; count < 10000; count++ )
  {
  char c = *sizePoint;
  if( c == 0 )
    break;

  sizePoint++;
  howMany++;
  }

return howMany;
}




/*
From my Java StrA class.


  public StrA( StrA in1, StrA in2 )
    {
    int max = in1.values.length + in2.values.
                                          length;
    char[] both = new char[max];

    int where = 0;
    int last = in1.values.length;
    for( int count = 0; count < last; count++ )
      {
      both[where] = in1.values[count];
      where++;
      }

    last = in2.values.length;
    for( int count = 0; count < last; count++ )
      {
      both[where] = in2.values[count];
      where++;
      }

    values = both;
    }


  private boolean searchTextMatches( int position,
                                char[] toSearch,
                                char[] toFind )
    {
    int findLength = toFind.length;
    if( findLength < 1 )
      return false;

    // Count goes from 0 to sLength - 1.
    if( (position + findLength - 1) >=
                                toSearch.length )
      return false;

    for( int count = 0; count < findLength;
                                        count++ )
      {
      if( toSearch[position + count] !=
                                   toFind[count] )
        return false;

      }

    return true;
    }



  public StrA replace( StrA toFind,
                       StrA replaceA )
    {
    if( values.length == 0 )
      return Empty;

    if( toFind.length() == 0 )
      return new StrA( values ); // this

    String testS = toString().replace(
                          toFind.toString(),
                          replaceA.toString() );

    // Replace might be an empty string.
    // if( replace.length() == 0 )

    if( values.length < toFind.length() )
      return  new StrA( values );

    StrABld resultBld = new StrABld(
                          values.length + 2048 );

    char firstChar = toFind.charAt( 0 );
    int last = values.length;
    int skip = 0;
    for( int count = 0; count < last; count++ )
      {
      if( skip > 0 )
        {
        skip--;
        if( skip > 0 )
          continue;

        }

      char testChar = values[count];
      if( testChar != firstChar )
        {
        resultBld.appendChar( testChar );
        continue;
        }

      if( !searchTextMatches( count,
                              values,
                              toFind.values ))
        {
        resultBld.appendChar( testChar );
        continue;
        }

      skip = toFind.length(); //  + 1;
      if( replaceA.length() > 0 )
        resultBld.appendArray( replaceA.values );

      }

    StrA result = resultBld.toStrA();

    String testResult = result.toString();
    if( !testResult.equals( testS ))
      {
      result = new StrA( "StrA Bad string: " +
            testResult + " and testS " + testS );
      return result;
      }

    return result;
    }



  public StrA replaceChar( char toFind,
                                  char replace )
    {
    if( values.length == 0 )
      return Empty;

    int last = values.length;
    char[] toArray = new char[last];
    for( int count = 0; count < last; count++ )
      {
      char testChar = values[count];
      if( testChar == toFind )
        toArray[count] = replace;
      else
        toArray[count] = testChar;

      }

    StrA result = new StrA( toArray );
    return result;
    }




  public StrArray splitChar( char delimit )
    {
    StrArray result = new StrArray();

    if( values.length == 0 )
      return result;

    StrABld sBld = new StrABld( 1024 * 64 );

    final int last = values.length;
    for( int count = 0; count < last; count++ )
      {
      char testChar = values[count];
      if( testChar == delimit )
        {
        result.append( sBld.toStrA());
        sBld.clear();
        }
      else
        {
        sBld.appendChar( testChar );
        }
      }

    if( sBld.length() > 0 )
      result.append( sBld.toStrA());

    return result;
    }



  public StrArray splitStrA( StrA delimit )
    {
    StrArray result = new StrArray();

    if( values.length == 0 )
      return result;

    if( delimit.length() == 0 )
      {
      result.append( new StrA( values )); // this
      return result;
      }

    if( values.length < delimit.length() )
      {
      result.append( new StrA( values )); // this
      return result;
      }

    StrABld sBld = new StrABld( values.length +
                                          2048 );

    char firstChar = delimit.charAt( 0 );
    final int last = values.length;
    int skip = 0;
    for( int count = 0; count < last; count++ )
      {
      if( skip > 0 )
        {
        skip--;
        if( skip > 0 )
          continue;

        }

      char testChar = values[count];
      if( testChar != firstChar )
        {
        sBld.appendChar( testChar );
        continue;
        }

      if( !searchTextMatches( count,
                              values,
                              delimit.values ))
        {
        sBld.appendChar( testChar );
        continue;
        }

      skip = delimit.length();
      result.append( sBld.toStrA() );
      sBld.clear();
      }

    if( sBld.length() > 0 )
      result.append( sBld.toStrA() );

    return result;
    }




  public StrA concat( StrA in )
    {
    if( in.length() == 0 )
      return this; // new StrA( values );

    int max = values.length + in.length();
    char[] both = new char[max];

    int where = 0;
    int last = values.length;
    for( int count = 0; count < last; count++ )
      {
      both[where] = values[count];
      where++;
      }

    last = in.length();
    for( int count = 0; count < last; count++ )
      {
      both[where] = in.charAt( count );
      where++;
      }

    return new StrA( both );
    }



  // Don't use equals() inherited from Object.
  public boolean equalTo( StrA in )
    {
    final int last = values.length;
    if( last != in.values.length )
      return false;

    for( int count = 0; count < last; count++ )
      {
      if( values[count] != in.values[count] )
        return false;

      }

    return true;
    }




  public boolean trimsToZero()
    {
    final int last = values.length;
    if( last == 0 )
      return true;

    for( int count = 0; count < last; count++ )
      {
      char testChar = values[count];
      if( testChar > ' ' )
        return false;

      }

    return true;
    }




  public StrA trimLeft()
    {
    StrABld sBld = new StrABld( values.length +
                                         1024 );
    int last = values.length;
    boolean foundFirst = false;
    for( int count = 0; count < last; count++ )
      {
      char testChar = values[count];
      if( foundFirst )
        {
        sBld.appendChar( testChar );
        continue;
        }

      if( testChar > ' ' )
        {
        foundFirst = true;
        sBld.appendChar( testChar );
        }
      }

    return sBld.toStrA();
    }



  public StrA trimRight()
    {
    StrABld sBld = new StrABld( values.length +
                                          1024 );
    final int last = values.length;
    boolean foundFirst = false;
    for( int count = last - 1; count >= 0;
                                        count-- )
      {
      char testChar = values[count];
      if( foundFirst )
        {
        sBld.appendChar( testChar );
        continue;
        }

      if( testChar > ' ' )
        {
        foundFirst = true;
        sBld.appendChar( testChar );
        }
      }

    return sBld.getReverse();
    }



  public StrA trim()
    {
    StrA result = trimRight();
    result = result.trimLeft();
    return result;
    }



  public StrA toLowerCase()
    {
    final int max = values.length;
    char[] lower = new char[max];
    for( int count = 0; count < max; count++ )
      {
      lower[count] = Character.toLowerCase(
                                values[count] );
      }

    return new StrA( lower );
    }



  public int compareToIgnoreCase( StrA in )
    {
    final int thisLen = values.length;
    final int inLen = in.values.length;
    int shorter = thisLen;
    if( inLen < shorter )
      shorter = inLen;

    StrA thisLower = toLowerCase();
    StrA inLower = in.toLowerCase();

    for( int count = 0; count < shorter; count++ )
      {
      if( thisLower.values[count] ==
                          inLower.values[count] )
        continue;

      return (int)thisLower.values[count] -
                (int)inLower.values[count];
      }

    if( thisLen == inLen )
      return 0;

    if( thisLen < inLen )
      return -1;
    else
      return 1;

    }



  public char firstNonSpaceChar()
    {
    final int max = values.length;
    if( max == 0 )
      return ' ';

    for( int count = 0; count < max; count++ )
      {
      char testChar = values[count];
      if( testChar != ' ' )
        return testChar;

      }

    return ' ';
    }




  public StrA replaceFirstChar( char toFind,
                                char replaceC )
    {
    final int max = values.length;
    if( max == 0 )
      return Empty;

    char[] resultA = new char[max];
    boolean foundFirst = false;
    for( int count = 0; count < max; count++ )
      {
      char testChar = values[count];
      if( !foundFirst )
        {
        if( testChar == toFind )
          {
          foundFirst = true;
          resultA[count] = replaceC;
          continue;
          }
        }

      resultA[count] = testChar;
      }

    return new StrA( resultA );
    }



  public StrA removeSections( char startChar,
                                 char endChar )
    {
    final int max = values.length;
    if( max == 0 )
      return Empty;

    StrABld sBld = new StrABld( max );
    boolean isInside = false;
    for( int count = 0; count < max; count++ )
      {
      char testChar = values[count];
      if( testChar == startChar )
        {
        isInside = true;
        continue;
        }

      if( testChar == endChar )
        {
        isInside = false;
        continue;
        }

      if( !isInside )
        sBld.appendChar( testChar );

      }

    return sBld.toStrA();
    }




  // This is a Cyclic Redundancy Check (CRC)
  // function.
  // CCITT is the international standards body.
  // This CRC function is translated from a
  // magazine
  // article in Dr. Dobbs Journal.
  // By Bob Felice, June 17, 2007
  // But this is my translation of what was in
  // that
  // article.  (It was written in C.)
  public int GetCRC16()
    {
    // Different Polynomials can be used.
    int Polynomial = 0x8408;
    int crc = 0xFFFF;

    final int last = values.length;
    if( last == 0 )
      return ~crc;

    int data = 0;
    for( int count = 0; count < last; count++ )
      {
      data = 0xFF & values[count];
      // For each bit in the data byte.
      for( int i = 0; i < 8; i++ )
        {
        if( 0 != ((crc & 0x0001) ^
                               (data & 0x0001)) )
          crc = (crc >> 1) ^ Polynomial;
        else
          crc >>= 1;

        data >>= 1;
        }
      }

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | ((data >> 8) & 0xFF);

    // Just make sure it's 16 bits.
    return crc & 0xFFFF;
    }



  public boolean containsChar( char toFind )
    {
    if( values.length == 0 )
      return false;

    final int last = values.length;
    for( int count = 0; count < last; count++ )
      {
      if( toFind == values[count] )
        return true;

      }

    return false;
    }



  public boolean containsStrA( StrA toFind )
    {
    if( values.length == 0 )
      return false;

    if( toFind.length() == 0 )
      return false;

    if( values.length < toFind.length() )
      return  false;

    char firstChar = toFind.charAt( 0 );
    final int last = values.length;
    for( int count = 0; count < last; count++ )
      {
      char testChar = values[count];
      if( testChar != firstChar )
        continue;

      if( searchTextMatches( count,
                              values,
                              toFind.values ))
        {
        return true;
        }
      }

    return false;
    }


  public boolean startsWithChar( char toFind )
    {
    if( values.length == 0 )
      return false;

    if( values[0] == toFind )
      return true;

    return false;
    }



  public boolean startsWith( StrA toFind )
    {
    if( values.length == 0 )
      return false;

    if( toFind.length() == 0 )
      return false;

    if( values.length < toFind.length() )
      return  false;

    char firstChar = toFind.charAt( 0 );
    char testChar = values[0];
    if( testChar != firstChar )
      return false;

    if( searchTextMatches( 0, values,
                                toFind.values ))
      return true;

    return false;
    }



  public StrA getReverse()
    {
    final int max = values.length;
    char[] result = new char[max];
    int where = 0;
    for( int count = max - 1; count >= 0;
                                       count-- )
      {
      result[where] = values[count];
      where++;
      }

    return new StrA( result );
    }



  public boolean endsWith( StrA toFind )
    {
    if( values.length == 0 )
      return false;

    if( toFind.length() == 0 )
      return false;

    if( values.length < toFind.length() )
      return  false;

    StrA toFindR = toFind.getReverse();
    StrA valuesR = getReverse();

    final int max = toFindR.length();
    for( int count = 0; count < max; count++ )
      {
      if( valuesR.values[count] !=
                        toFindR.values[count] )
        return false;

      }

    return true;
    }



  public boolean endsWithChar( char toFind )
    {
    if( values.length == 0 )
      return false;

    final int where = values.length - 1;
    if( values[where] == toFind )
      return true;
    else
      return false;

    }



  public StrA substring( int begin, int end )
    {
    if( begin < 0 )
      begin = 0;

    if( end < 0 )
      end = 0;

    if( end >= values.length )
      end = values.length - 1;

    if( begin > end )
      return Empty;

    StrABld sBld = new StrABld( end );
    for( int count = begin; count <= end; count++ )
      sBld.appendChar( values[count] );

    return sBld.toStrA();
    }



  public StrA cleanUnicodeField()
    {
    final int last = values.length;
    StrABld sBld = new StrABld( last );
    for( int count = 0; count < last; count++ )
      {
      char testC = values[count];
      if( testC == '\t' )
        testC = ' ';

      if( testC == '\n' )
        testC = ' ';

      if( testC < ' ' )
        testC = '#';

      if( testC >= UTF8StrA.HighSurrogate )
        testC = '%';

      // if( (testC > 126) && (testC < 256) )
        // testC = '*';

      if( Markers.isMarker( testC ))
        testC = '(';

      sBld.appendChar( testC );
      }

    return sBld.toStrA();
    }



  }
*/
