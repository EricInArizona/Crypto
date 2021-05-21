// Copyright Eric Chauvin 2021.



#include "RandomCrypto.h"



#include <random>



void RandomCrypto::makeRandomBytes(
                                Uint8Array& u8a,
                                Uint32 howMany )
{
u8a.clear();

std::random_device rd;
// rd.entropy()
// rd.min()
// rd.max()

// std::mersenne_twister_engine
// std::mt19937_64

std::mt19937 gen( rd() );
//std::uniform_int_distribution<> dist( 1,
//                               0xFFFFFFFF );

Uint32 gotCount = 0;
for( Uint32 count = 0; count < 100000; count++ )
  {
  // dist( gen())
  Uint8 c = (Uint8)gen();
  if( c == 0 )
    continue;

  u8a.appendVal( c );
  gotCount++;
  if( gotCount >= howMany )
    return;

  }
}
