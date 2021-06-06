// Copyright Eric Chauvin, 2021.



#ifndef TimeEC_H
#define TimeEC_H



#include "BasicTypes.h"
#include "Str.h"



class TimeEC
  {
  private:
  Int64 timeSeconds = 0; // Seconds since Jan 1,
                         // 1970.

  Int32 seconds = 0;
  Int32 minutes = 0;
  Int32 hour = 0;
  Int32 day = 0;
  Int32 month = 0;
  Int32 year = 0;
  Int32 weekDay = 0; // Sunday = 0
  Int32 yearDay = 0; // day of year to 365.
  Int32 dayLightSavings = 0;

  public:
  TimeEC( void );
  void setNow( void );
  Int64 diffSec( TimeEC& in );
  Str timeStr( void );


  };


#endif
