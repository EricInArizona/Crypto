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

for( Uint32 count = 0; count < howMany; count++ )
  u8a.appendVal( (Uint8)gen());

//  u8a.appendVal( (Uint8)dist( gen()));

}
