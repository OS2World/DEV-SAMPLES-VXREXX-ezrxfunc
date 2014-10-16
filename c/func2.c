/*
 * func2.c -- Another example of a simple REXX function.
 */

#include "standard.h"
#include "rxsutils.h"

/*
 * Declare our exported function.  Export it!
 */

RexxFunctionHandler EZFunc2;

/*
 * EZFunc2 -- Returns the name of the function that you called.  This
 *            function will be registered as both 'EZFunc2' and 'EZFunc3'.
 */

ULONG EZFunc2( CHAR *name, ULONG numargs, RXSTRING args[],
               CHAR *queuename, RXSTRING *retstr )
  {
    PSZ tmp;

    place_holder( queuename );

    /* Make sure we have only one argument, and that it's not a
       null string... */

    if( numargs != 1 ) goto error;
    if( args[0].strptr == NULL || args[0].strlength == 0 ) goto error;

    /* Get some buffer space.... */

    tmp = malloc( strlen( name ) + args[0].strlength + 100 );
    if( !tmp ) goto error;

    /* Return the name of the func and the argument */

    sprintf( tmp, "EZFunc2 (called as '%s') called with argument '%s'",
             name, args[0].strptr );

    CopyResult( tmp, strlen( tmp ), retstr );

    free( tmp );

    return( VALID_ROUTINE );

  error:
    return( INVALID_ROUTINE );
}

