// Copyright Eric Chauvin 2022.



#include "FindFactorsCrt.h"
#include "Crt2.h"



FindFactorsCrt::FindFactorsCrt( void )
{
}


FindFactorsCrt::FindFactorsCrt(
                      const FindFactorsCrt& in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy c for FindFactorsCrtCrt2.";
}


FindFactorsCrt::~FindFactorsCrt( void )
{
}



bool FindFactorsCrt::getSmall( Integer& pubKeyN,
                         Integer& find1,
                         Integer& find2,
                         IntegerMath& intMath,
                         SPrimes& sPrimes,
                         MultInv& multInv,
                         CrtMath& crtMath )
{
Crt prod;
prod.setFromInteger( pubKeyN,
                     intMath,
                     sPrimes );

Crt2 prime1;
Crt2 prime2;
Crt crt;
Crt inv;

for( Uint32 count = 1; count < 5; count++ )
  {
  prime1.setToIndex1( count );
  prime1.incRev( sPrimes, count );

  for( Uint32 countI = 0; countI < 5; countI++ )
    {
    if( !prime1.incRev( sPrimes, count ))
      break;

    if( !prime1.setInvCrt( crt,
                           inv,
                           sPrimes,
                           multInv,
                           crtMath ))
      continue;

    }


  }

find1.setToOne();
find2.setToOne();

return true;
}
