// Copyright Eric Chauvin 2021 - 2022.



#include "RandomCrypto.h"
#include <random>
#include "CastE.h"



void RandomCrypto::makeRandomBytes(
                            UTF16Buf& cBuf,
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

// Make a uniform distribution:
//std::uniform_int_distribution<> dist( 1,
//                               0xFFFFFFFF );

Int32 gotCount = 0;
for( Int32 count = 0; count < 100000; count++ )
  {
  // dist( gen())
  UTF16 c = CastE::U64ToUTF16Byte( gen());
  if( c == 0 )
    continue;

  cBuf.appendVal( c );
  gotCount++;
  if( gotCount >= howMany )
    return;

  }
}
