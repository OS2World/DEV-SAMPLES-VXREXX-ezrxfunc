/*
 * func1.c -- Example of a simple REXX function.
 */

#include "standard.h"

#define INCL_DOS
#include <os2.h>

#include "rxsutils.h"

/*
 * Declare our exported function.  Don't forget to export it!
 */

RexxFunctionHandler EZFunc1;

/*
 * EZFunc1 -- Bumps a counter and returns a string.  Arguments are as
 *            follows:
 *
 *              name -- Name of function being called.
 *              numargs -- Number of argument strings passed from REXX.
 *              args -- Array of argument strings passed from REXX.
 *              queuename -- Name of currently active queue.
 *              retstr -- Pointer to buffer for result string.
 *
 *            The only one you may modify is the retstr.
 */

ULONG EZFunc1( CHAR *name, ULONG numargs, RXSTRING args[],
               CHAR *queuename, RXSTRING *retstr )
  {
    static ULONG count = 0;
    char         buf[ 100 ];

    place_holder( name );
    place_holder( queuename );
    place_holder( args );

    /* Check # of arguments.  We don't want any.  Exit with error
       (which halts the REXX program) if some are given. */

    if( numargs > 0 ) goto error;

    /* Enter a critical section.  Because the counter is static, it
       will be shared across threads, so we need to update it atomically. */

    DosEnterCritSec();

    sprintf( buf, "You called EZFunc1 %d times.", ++count );

    DosExitCritSec();

    /* Set the retstr to the new string. */

    CopyResult( buf, strlen( buf ), retstr );

    /* Return 0 if no error occurred */

    return( VALID_ROUTINE );

    /* If a syntax error of some kind occurs (too few/many args, bad args)
       then return an errorcode of 40 */

  error:
    return( INVALID_ROUTINE );
}

