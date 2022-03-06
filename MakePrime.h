// Copyright Eric Chauvin, 2022.



#pragma once



#include "../LinuxApi/BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "Mod.h"



class MakePrime
  {
  private:
  Int32 testForCopy = 123;

  public:
  MakePrime( void );
  MakePrime( const MakePrime& in );
  ~MakePrime( void  );
  void makeIt( Integer& result,
               const Int32 indexSize,
               const SPrimes& sPrimes,
               IntegerMath& intMath,
               Mod& mod );

  };
