// Copyright Eric Chauvin 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#include "../CppBase/Casting.h"

#include "CrtTreeL.h"



CrtTreeL::CrtTreeL( void )
{
i32Arrays = new Int32Array[Casting::i32ToU64( last )];

indexAr.setSize( last );
}



CrtTreeL::CrtTreeL( const CrtTreeL& in )
{
i32Arrays = new Int32Array[Casting::i32ToU64(
                                      last )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for CrtTreeL.";
}


CrtTreeL::~CrtTreeL( void )
{
delete[] i32Arrays;
}



void CrtTreeL::init( const SPrimes& sPrimes, const GoodX& goodX )
{
for( Int32 count = 0; count < last; count++ )
  {
  Int32 prime = sPrimes.getPrimeAt( count );
  i32Arrays[count].setSize( prime );

  for( Int32 countP = 0; countP < prime;
                                    countP++ )
    {
    if( goodX.getVal( count, countP ))
      i32Arrays[count].appendVal( countP );

    }
  }
}




void CrtTreeL::setFirstGoodXToDepth( Int32 depth )
{
RangeC::test2( depth, 0, last - 1,
         "setFirstGoodXToDepth  depth range." );

const Int32 max = index;
for( Int32 count = depth; count <= max; count++ )
  {
  setFirstGoodXAt( count );
  }
}
