// Copyright Eric Chauvin 2021 - 2022.



#include "Base10Number.h"



Base10Number::Base10Number( Str& toSet )
{
D = new Int32[digitArraySize];
setFromStr( toSet );
}


// The copy constructor.
Base10Number::Base10Number(
                        const Base10Number& obj )
{
D = new Int32[digitArraySize];

for( Int32 count = 0; count < digitArraySize;
                                        count++ )
  {
  D[count] = obj.D[count];
  }

// StIO::printFS(
  // "Base10Number copy constructor called.\n" );
}


Base10Number::~Base10Number( void )
{
delete[] D;
}



Int32 Base10Number::getD( Int32 where )
{
if( where >= digitArraySize )
  throw "getD() index out of bounds.";

return D[where];
}


Int32 Base10Number::convertDigit( Int32 digit )
{
if( (digit > '9') || (digit < '0') )
  throw "Base10Number: convertDigit().";

return (digit - '0');
}



void Base10Number::setFromStr( Str& toSet )
{
index = 0;
D[0] = 0;

const Int32 last = toSet.getSize();
if( last < 1 )
  return;

Int32 where = 0;
for( Int32 count = last - 1; count >= 0; count-- )
  {
  if( where >= digitArraySize )
    throw "Base10Number: Too big for array.";

  Int32 c = toSet.charAt( count );

  // Ignore white space, commas, non digits.
  if( (c < '0') || (c > '9'))
    continue;

  Int32 digit = convertDigit( c );

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
