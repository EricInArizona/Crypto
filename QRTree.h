// Copyright Eric Chauvin 2022.



#pragma once



#include "BasicTypes.h"
#include "QRTreeNode.h"
#include "GoodX.h"


class QRTree
  {
  private:
  Int32 testForCopy = 123;

  QRTreeNode* nodesAr;
  static const Int32 arraySize =
                   ProjConst::crtDigitArraySize;

  // Int32 length = 0;
  // Int32 maxLength = 7;

  public:
  QRTree( void );
  QRTree( const QRTree& in );
  ~QRTree( void );

  };
