// Copyright Eric Chauvin 2021 - 2022.



#pragma once


// A Number System used for Modular Reduction.


// An early version of this idea is in old code
// I wrote from 2015 and earlier at:
// https://github.com/Eric7Apps/OldCode/
       //     blob/master/ModularReduction.cs


#include "../LinuxApi/BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "ProjConst.h"
#include "IntBuf.h"



class NumbSys
  {
  private:
  Int32 testForCopy = 123;
  static const Int32 last =
                      ProjConst::digitArraySize;

  Integer currentBase;
  Integer numVal;
  IntBuf* intBufAr;

  void setupBaseArray( const Integer& setBase,
                       IntegerMath& intMath );

  public:
  NumbSys( void );
  NumbSys( const NumbSys& in );
  ~NumbSys( void );

  void reduce( Integer& result,
               const Integer& toReduce,
               const Integer& modulus,
               IntegerMath& intMath );

  };
