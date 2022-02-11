// Copyright Eric Chauvin 2022.


#pragma once


#include "BasicTypes.h"


// This is meant to be used only by QRTree.
// No nested classes.


class QRTreeNode
  {
  private:
  // Int32 testForCopy = 123;

  // This structure is too simple now, but
  // I want to be able to add things later.
  // And some new idea I haven't thought
  // of yet.

  // An optimization for later:
  // Int32 accumByte = 0;
  // accumByte up to this node in the tree.

  public:
  Int32 digit = 0;

  // QRTreeNode( void );
  // QRTreeNode( const QRTreeNode& in );
  // ~QRTreeNode( void );

/*
  inline Int32 getAccumByte( void )
    {
    return accumByte;
    }

  inline Int32 setAccumByte(
                    const Int32 lowerAccumB,
                    const Int32 crtByte )
    {
    // crtByte is crtMath.getBaseByte( count );

    Int32 result = crtByte * digit;
    result += lowerAccumB;
    result = result & 0xFF;

    accumByte = result;
    return result;
    }
*/

  };
