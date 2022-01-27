// Copyright Eric Chauvin 2021 - 2022.



#include "RandomCrypto.h"
#include <random>



void RandomCrypto::makeRandomBytes(
                            Int8Array& i8a,
                            const Int32 howMany )
{
i8a.clear();

std::random_device rd;
// rd.entropy()
// rd.min()
// rd.max()

// std::mersenne_twister_engine
// std::mt19937_64

std::mt19937 gen( rd() );
//std::uniform_int_distribution<> dist( 1,
//                               0xFFFFFFFF );

Int32 gotCount = 0;
for( Int32 count = 0; count < 100000; count++ )
  {
  // dist( gen())
  Int8 c = gen();
  if( c == 0 )
    continue;

  i8a.appendVal( c );
  gotCount++;
  if( gotCount >= howMany )
    return;

  }
}
