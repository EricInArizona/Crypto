// Copyright Eric Chauvin 2021.



#include "CharBuf.h"
#include "StIO.h"


CharBuf::CharBuf( void )
{
arraySize = 1024 * 64;
cArray = new char[arraySize];

StIO::uPrintf( "CharBuf constructor called.\n" );
}


// The copy constructor.
CharBuf::CharBuf( const CharBuf &obj )
{
// Don't copy a giant buffer.

const char* showS = "The CharBuf copy constructor"
         " should not be getting called.\n";
throw showS;
}



CharBuf::~CharBuf( void )
{
delete[] cArray;

StIO::uPrintf( "CharBuf destructor called.\n" );
}



void CharBuf::increaseSize( Uint32 howMuch )
{
arraySize = arraySize + howMuch;
Uint16* tempArray = new Uint16[arraySize];

const Uint32 max = last;

for( Uint32 count = 0; count < max; count++ )
  tempArray[count] = cArray[count];

delete[] cArray;
cArray = new char[arraySize];

for( Uint32 count = 0; count < max; count++ )
  cArray[count] = tempArray[count];

delete[] tempArray;
}



void CharBuf::appendChars( const char* fromBuf,
                           Uint32 howMany )
{
if( ((last + 2) + howMany) <= arraySize )
  increaseSize( howMany + (1024 * 64) );

for( Uint32 count = 0; count < howMany; count++ )
  {
  cArray[last] = *fromBuf;
  last++;
  fromBuf++;
  }
}



void CharBuf::appendStr( Str& in )
{
Uint32 howMany = in.getSize();
if( ((last + 2) + howMany) <= arraySize )
  increaseSize( howMany + (1024 * 64) );

for( Uint32 count = 0; count < howMany; count++ )
  {
  cArray[last] = in.charAt( count );
  last++;
  }
}
