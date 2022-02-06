// Copyright Eric Chauvin, 2021.



#include "TimeEC.h"
#include "CharBuf.h"
#include <ctime>


TimeEC::TimeEC( void )
{
setNow();
}



void TimeEC::setNow( void )
{
time_t rawtime;

time( &rawtime );
timeSeconds = rawtime;

struct tm buf;
// errno_t errorNumber = localtime_s( &buf,
localtime_s( &buf, &rawtime );

// StIO::printFS( "Year:\n" );
// StIO::printFUD( 1900 + buf.tm_year );
// StIO::printFS( "\n" );

seconds = buf.tm_sec;
minutes = buf.tm_min;
hour = buf.tm_hour;
day = buf.tm_mday;
month = buf.tm_mon;
year = 1900 + buf.tm_year;
weekDay = buf.tm_wday; // Sunday = 0
yearDay = buf.tm_yday; // day of year to 365.
dayLightSavings = buf.tm_isdst;
}



Int64 TimeEC::diffSec( TimeEC& in )
{
return timeSeconds - in.timeSeconds;
}



Str TimeEC::timeStr( void )
{
CharBuf cBuf;


Str colon( ":" );
Str secS( seconds );
Str minS( minutes );
Str hourS( hour );

// Close enough for now.
cBuf.appendStr( hourS );
cBuf.appendStr( colon );
cBuf.appendStr( minS );
cBuf.appendStr( colon );
cBuf.appendStr( secS );

return cBuf.getStr();
}
