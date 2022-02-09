// Copyright Eric Chauvin 2022.



#include "QRTree.h"
#include "CastE.h"


QRTree::QRTree( void )
{
nodesAr = new QRTreeNode[
                CastE::i32ToU64( arraySize )];



QRTree::QRTree( const QRTree& in )
{
nodesAr = new QRTreeNode[
                   CastE::i32ToU64( arraySize )];

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constr for QRTree.";
}


QRTree::~QRTree( void )
{
delete[] nodesAr;
}


void QRTree::increaseSize(
                        const Int32 howMuch )
{
arraySize = arraySize + howMuch;
QRTreeNode* tempArray = new QRTreeNode[
                 CastE::i32ToU64( arraySize )];

const Int32 max = last;

for( Int32 count = 0; count < max; count++ )
  tempArray[count].copy( nodesAr[count] );

delete[] nodesAr;
nodesAr = new QRTreeNode[
                  CastE::i32ToU64( arraySize )];

for( Int32 count = 0; count < max; count++ )
  nodesAr[count].copy( tempArray[count] );

delete[] tempArray;
}



Int32 QRTree::addNewCopy( QRTreeNode& tNode )
{
for( Int32 count = 0; count < last; count++ )
  {
  // If it's not in use.
  if( nodesAr[count].index == -1 )
    {
    nodesAr[count].copy( tNode );
    nodesAr[count].index = count;
    return count;
    }
  }

if( last >= arraySize )
  throw "QRTree::addNode last >= arraySize";

nodesAr[last].copy( tNode );
nodesAr[last].index = last;

Int32 result = last;

last++;
if( last >= arraySize )
  increaseSize( 1024 * 64 );

return result;
}



void QRTree::removeNode( const Int32 where )
{
if( where < 0 )
  throw "QRTree.removeNode where < 0";

if( where >= last )
  throw "QRTree.removeNode where >= last";

// Call this recursively for the sub node.
// And the sub nodes that the sub node has.
removeNode( nodesAr[where].subnode );

// Mark it as not in use.
nodesAr[where].index = -1;
}



void QRTree::isGoodX( const Int32 where,
                      const GoodX& goodX );
{
    Int32 test = crtDigit;
    test = test * digit;
    test  += accum;
    test = test % prime;
    return test;

      if( goodX.getVal( where, test ))

}
