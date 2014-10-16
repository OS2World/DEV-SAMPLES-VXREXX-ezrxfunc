/*
 * initterm.c -- The functions in this file are called when the DLL is
 *               loaded and unloaded.  What "loaded" and "unloaded" mean
 *               is defined in the .DEF file.  In our case, it means that
 *               whenever a _process_ first loads or unloads the DLL, call
 *               these routines.
 */

#include "standard.h"

#define INCL_DOS
#include <os2.h>

/*
 * __dll_initialize -- Initialize the DLL.  In this case we don't do
 *                     anything.  The C library has already been
 *                     initialized.
 */

int __dll_initialize( void )
  {
    return( TRUE );
  }

/*
 * __dll_terminate -- Clean things up.  The C library will be closed
 *                    after this call.
 */

int __dll_terminate( void )
  {
    return( TRUE );
  }

/*
 * The following code is CSET-specific.  OS/2 actually calls the
 * _DLL_InitTerm function directly.  In WATCOM C, this function is in
 * the library and it calls the functions __dll_initialize and
 * __dll_terminate that you define.  So for consistency, with CSET
 * we'll do the appropriate C library stuff and then call those same
 * functions above.  So don't modify this section unless you know
 * what you're doing.
 */

#ifdef __IBMC__

extern int  _CRT_init( void );
extern void _CRT_term( void );

/*
 * _DLL_InitTerm -- Called by the system (hence uses _System linkage)
 *          the first time the DLL is loaded or the last time
 *          it is freed for a particular process.
 */

unsigned long _System _DLL_InitTerm( ULONG hModule, ULONG ulFlag )
  {
    long ok = FALSE;

    /*
     * If ulFlag is zero then the DLL is being loaded so initialization
     * should be performed.  If ulFlag is 1 then the DLL is being freed so
     * termination should be performed.             
     */

    place_holder( hModule );

    if( ulFlag == 0 ){

        /* The C run-time environment initialization function must be called */
        /* before any calls to C run-time functions that are not inlined.    */

        if( _CRT_init() == -1 )
            goto leave;

        if( !__dll_initialize() ) goto leave;

    } else if( ulFlag == 1 ){

        __dll_terminate();

        _CRT_term();
    }

    /* A non-zero value must be returned to indicate success. */

    ok = TRUE;

  leave:
    return( ok );
  }

#endif

