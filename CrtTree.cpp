// Copyright Eric Chauvin 2022.



#include "CrtTree.h"


CrtTree::CrtTree( void )
{
digitsAr.setSize( last );
}


CrtTree::CrtTree( const CrtTree& in )
{
// digitsAr.setSize( last );

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constr for CrtTree.";
}


CrtTree::~CrtTree( void )
{
// digitsAr
}



void CrtTree::setFirstGoodXToDepth(
                      Int32 depth,
                      const GoodX& goodX )
{
RangeC::test2( depth, 0, last - 1,
         "setFirstGoodXToDepth  depth range." );

const Int32 max = index;
for( Int32 count = depth; count <= max; count++ )
  {
  setFirstGoodXAt( count, goodX );
  }
}
