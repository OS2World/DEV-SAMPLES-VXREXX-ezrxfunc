/*
 * funcload.c -- Defines the two functions 'EZLoadFuncs' and 'EZDropFuncs',
 *               which load/drop all the functions defined in this DLL.
 */

#include "standard.h"
#include "rxsutils.h"

/* Change this if you're changing the DLL name... */

#ifndef DLLNAME
#define DLLNAME "EZRXFUNC"
#endif

/*
 * Declare our functions.  Make sure to export these in the * .DEF file!
 */

RexxFunctionHandler EZLoadFuncs;
RexxFunctionHandler EZDropFuncs;

/*
 * Define the table that lists REXX function names and the corresponding
 * DLL entry point.  You must change this table whenever you add/remove
 * a function or entry point.
 */

typedef struct fncEntry {
    PSZ     rxName;
    PSZ     cName;
} fncEntry, *fncEntryPtr;

static fncEntry RxFncTable[] =
   {
        /* function */  /* entry point */
      { "EZLoadFuncs",  "EZLoadFuncs"   },
      { "EZDropFuncs",  "EZDropFuncs"   },
      { "EZFunc1",      "EZFunc1"       },
      { "EZFunc2",      "EZFunc2"       },
      { "EZFunc3",      "EZFunc2"       }  /* yes, EZFunc2 is intentional! */
   };

/*
 * EZLoadFuncs -- Register all the functions with REXX.
 */

ULONG EZLoadFuncs( CHAR *name, ULONG numargs, RXSTRING args[],
                   CHAR *queuename, RXSTRING *retstr )
  {
    int entries;
    int j;

    place_holder( args );
    place_holder( queuename );
    place_holder( name );
    
    retstr->strlength = 0;

    if( numargs > 0 ) goto error;

    entries = sizeof( RxFncTable ) / sizeof( fncEntry );

    for( j = 0; j < entries; ++j ){
        RexxRegisterFunctionDll( RxFncTable[ j ].rxName, DLLNAME,
          RxFncTable[ j ].cName );
    }

    return( VALID_ROUTINE );

  error:
    return( INVALID_ROUTINE );
}

/*
 * EZDropFuncs -- Deregister all the functions with REXX.
 */

ULONG EZDropFuncs( CHAR *name, ULONG numargs, RXSTRING args[],
                   CHAR *queuename, RXSTRING *retstr )
  {
    int entries;
    int j;

    place_holder( args );
    place_holder( queuename );
    place_holder( name );

    retstr->strlength = 0;

    if( numargs > 0 ) goto error;

    entries = sizeof( RxFncTable ) / sizeof( fncEntry );

    for( j = 0; j < entries; ++j ){
        RexxDeregisterFunction( RxFncTable[ j ].rxName );
    }

    return( VALID_ROUTINE );

  error:
    return( INVALID_ROUTINE );
}

