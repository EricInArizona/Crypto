// Copyright Eric Chauvin 2022.


#pragma once


#include "BasicTypes.h"


// This is meant to be used only by QRTree.

class QRTreeNode
  {
  private:
  // Int32 testForCopy = 123;

  Int32 accumByte = 0;

  public:
  Int32 digit = 0;

  // QRTreeNode( void );
  // QRTreeNode( const QRTreeNode& in );
  // ~QRTreeNode( void );


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


  };
