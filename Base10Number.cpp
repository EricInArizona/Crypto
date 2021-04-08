// Copyright Eric Chauvin 2021.



#include "Base10Number.h"
#include "FileUtil.h"



Base10Number::Base10Number( Str toSet )
{
FileUtil::uPrintf( "Constructor called.\n" );
D = new Uint16[digitArraySize];
setFromStr( toSet );

FileUtil::uPrintf( "End of constructor.\n" );
}



Base10Number::~Base10Number( void )
{
FileUtil::uPrintf( "Destructor called.\n" );

delete[] D;

FileUtil::uPrintf( "End of Destructor.\n" );
}



Uint32 Base10Number::getD( Uint32 where )
{
if( where >= digitArraySize )
  throw "getD() index out of bounds.";

return D[where];
}


Uint16 Base10Number::convertDigit( Uint16 digit )
{
if( (digit > '9') || (digit < '0') )
  throw "Base10Number: convertDigit().";

return (Uint16)(digit - '0');
}



void Base10Number::setFromStr( Str toSet )
{
index = 0;

const Int32 last = toSet.getArraySize();
FileUtil::uPrintf( "Array size: " );
FileUtil::uPrintfD( last );
FileUtil::uPrintf( "\n" );

if( last < 1 )
  return;

Uint32 where = 0;
for( Int32 count = last - 1; count >= 0; count-- )
  {
  if( where >= digitArraySize )
    throw "Base10Number: Too big for array.";

  Uint16 c = toSet.uCharAt( count );

  // Ignore white space, commas, non digits.
  if( (c < '0') || (c > '9'))
    continue;

  Uint16 digit = convertDigit( c );

  // Test what convertDigit() returned.
  if( digit > 9 )
    throw "Base10Number: digit > 9.";

  D[where] = digit;
  where++;
  }

if( where == 0 )
  {
  // No valid digit was ever set.
  throw "Base10Number: no valid digits.";
  }

index = where - 1;
}
