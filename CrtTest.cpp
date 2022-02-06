// CrtTest


/*
bool RSA::crtTest( const Integer& t1,
                   const CrtMath& crtMath,
                   FileIO& mainIO,
                   const MultInv& multInv )
{
Int32 prime = sPrimes.getPrimeAt(
           ProjConst::crtDigitArraySize - 1 );

mainIO.appendChars( "\n\nLast CRT prime is: " );
Str showIt( prime );
mainIO.appendStr( showIt );
mainIO.appendChars( "\n" );


Int32 bigPrime = sPrimes.getBiggestPrime();
mainIO.appendChars( "Biggest prime is: " );
Str showIt2( bigPrime );
mainIO.appendStr( showIt2 );
mainIO.appendChars( "\n\n" );


Crt test1;
test1.setFromInteger( t1, intMath, sPrimes );

Integer accum;

Crt2 test2;

test2.setFromCrt( test1,
                  // accum,
                  crtMath,
                  sPrimes,
                  // intMath
                  multInv
                  );

Crt test3;
test2.setCrt( test3, crtMath, sPrimes );

if( !test3.isEqual( test1 ))
  throw "!test3.isEqual( test1 )";


// if( !accum.isEqual( t1 ))
  // return false;

Integer result;


test2.toInteger( crtMath, result, intMath );

// If ProjConst::crtDigitArraySize is too
// small then toInteger() will come out too
// small.

if( !result.isEqual( t1 ))
  return false;

return true;
}
*/
