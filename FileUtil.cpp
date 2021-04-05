// Copyright Eric Chauvin 2021.



#include "FileUtil.h"
#include <stdio.h>


// extern "C" {


void FileUtil::uPrintf( const char* toWrite )
{
// printf( "Testing.\n" );
printf( "%s", toWrite );
}


void FileUtil::uPrintfD( Uint32 d )
{
printf( "%d", d );

}
