// Copyright Eric Chauvin 2021.



#include "StIO.h"
#include <stdio.h>


// extern "C" {


void StIO::uPrintf( const char* toWrite )
{
// printf( "Testing.\n" );
printf( "%s", toWrite );
}


void StIO::uPrintfD( Uint32 d )
{
printf( "%d", d );
}


void StIO::putC( char c )
{
putchar( c );
}

