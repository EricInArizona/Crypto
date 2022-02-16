// Copyright Eric Chauvin 2022.



#include "CrtTree.h"
#include "CastE.h"
// #include "Division.h" Do Division with Crt2.


CrtTree::CrtTree( void )
{
nodesAr = new Int32[CastE::i32ToU64( last )];
}


CrtTree::CrtTree( const CrtTree& in )
{
nodesAr = new Int32[CastE::i32ToU64( last )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constr for CrtTree.";
}


CrtTree::~CrtTree( void )
{
delete[] nodesAr;
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
