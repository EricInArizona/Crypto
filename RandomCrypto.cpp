// Copyright Eric Chauvin 2021 - 2022.



#include "RandomCrypto.h"
#include <random>
#include "CastE.h"



void RandomCrypto::makeRandomBytes(
                            CharBuf& cBuf,
                            const Int32 howMany )
{
cBuf.clear();

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
  char c = CastE::i32ToChar(
              CastE::U64ToI32( gen()));
  if( c == 0 )
    continue;

  cBuf.appendVal( c );
  gotCount++;
  if( gotCount >= howMany )
    return;

  }
}
