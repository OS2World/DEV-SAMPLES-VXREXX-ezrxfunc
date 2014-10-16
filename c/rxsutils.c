/*
 * rxsutils.c -- REXX String utilities.  Various utility functions to do
 *               string to type conversions and back.  You don't need to
 *               use these, but they may be useful to you.
 */

#include "standard.h"

#define INCL_DOS
#include <os2.h>
#include <rexxsaa.h>

#include "rxsutils.h"

#define MAX_NUM_STRING_LEN  20

/*
 * CopyResult -- Copies a string into a result, allocating space for it
 *               if necessary.  If you pass it an RXSTRING with a non-null
 *               buffer and a non-zero length, it will try to copy the
 *               data into that buffer.  Otherwise is uses DosAllocMem
 *               to allocate a new one.
 */

void CopyResult( char *src, ULONG len, PRXSTRING dest )
  {
    void *mem = NULL;

    if( !dest ) goto leave;

    if( ( !src || len == 0 ) && dest->strptr != NULL ){
        SetNullRXString( dest );
    } else if( dest->strptr != NULL && len <= dest->strlength ){
        memset( dest->strptr, 0, dest->strlength );
        memcpy( dest->strptr, src, len );
        dest->strlength = len;
    } else {
        /* OK, at this point we've determined the buffer is too small
           for use to use, so we'll allocate a new one */

        SetNullRXString( dest );

        if( DosAllocMem( &mem, len + 1, PAG_COMMIT | PAG_WRITE | PAG_READ ) )
            goto leave;

        dest->strptr    = mem;
        dest->strlength = len;

        memset( dest->strptr, 0, len + 1 );
        memcpy( dest->strptr, src, len );
    }

  leave:
    return;
  }

/*
 * SetNullRXString -- Sets an RXSTRING to a null string.
 */

void SetNullRXString( PRXSTRING str )
  {
    if( str ){
        if( str->strptr ){
            str->strptr[0] = NULLCHAR;
        }

        str->strlength = 0;
    }
  }

/*
 * The following functions were defined for use with WATCOM C.  They may
 * work on other systems, but first you have to remove the #ifdef below
 */
 
#ifdef __WATCOMC__

/*
 * AllocNumSpace -- Allocate enough memory for a number.
 */

static BOOL AllocNumSpace( PRXSTRING str )
  {
    if( !str ) goto error;

    if( str->strptr == NULL || str->strlength < MAX_NUM_STRING_LEN + 1 ){
        if( DosAllocMem( (PPVOID) &str->strptr, MAX_NUM_STRING_LEN + 1,
                         PAG_COMMIT | PAG_WRITE | PAG_READ ) != 0 ) goto error;
    }

    memset( str->strptr, 0, MAX_NUM_STRING_LEN + 1 );
    str->strlength = MAX_NUM_STRING_LEN;

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * RXStringToULong
 */

BOOL RXStringToULong( PRXSTRING str, PULONG val )
  {
    char *end;

    if( !str || !val || str->strptr == NULL || str->strlength == 0 ) goto error;

    errno = 0;
    *val  = strtoul( str->strptr, &end, 10 );
    if( errno != 0 ) goto error;

    while( isspace( *end ) ){
        ++end;
    }

    if( *end != NULLCHAR ) goto error;

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * ULongToRXString
 */

BOOL ULongToRXString( ULONG val, PRXSTRING str )
  {
    if( !AllocNumSpace( str ) ) goto error;

    str->strlength = sprintf( str->strptr, "%lu", val );

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * RXStringToLong
 */

BOOL RXStringToLong( PRXSTRING str, PLONG val )
  {
    char *end;

    if( !str || !val || str->strptr == NULL || str->strlength == 0 ) goto error;

    errno = 0;
    *val  = strtol( str->strptr, &end, 10 );
    if( errno != 0 ) goto error;

    while( isspace( *end ) ){
        ++end;
    }

    if( *end != NULLCHAR ) goto error;

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * LongToRXString
 */

BOOL LongToRXString( LONG val, PRXSTRING str )
  {
    if( !AllocNumSpace( str ) ) goto error;

    str->strlength = sprintf( str->strptr, "%ld", val );

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * RXStringToUShort
 */

BOOL RXStringToUShort( PRXSTRING str, PUSHORT val )
  {
    long l;
    char *end;

    if( !str || !val || str->strptr == NULL || str->strlength == 0 ) goto error;

    *val  = 0;
    errno = 0;
    l     = strtol( str->strptr, &end, 10 );
    if( errno != 0 ) goto error;

    while( isspace( *end ) ){
        ++end;
    }

    if( *end != NULLCHAR ) goto error;

    if( l < 0 || l > 65535 ) goto error;

    *val = (USHORT) l;

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * UShortToRXString
 */

BOOL UShortToRXString( USHORT val, PRXSTRING str )
  {
    if( !AllocNumSpace( str ) ) goto error;

    str->strlength = sprintf( str->strptr, "%u", val );

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * RXStringToShort
 */

BOOL RXStringToShort( PRXSTRING str, PSHORT val )
  {
    long  l;
    char *end;

    if( !str || !val || str->strptr == NULL || str->strlength == 0 ) goto error;

    *val  = 0;
    errno = 0;
    l     = strtol( str->strptr, &end, 10 );
    if( errno != 0 ) goto error;

    while( isspace( *end ) ){
        ++end;
    }

    if( *end != NULLCHAR ) goto error;

    if( l < -32768 || l > 32767 ) goto error;

    *val = (SHORT) l;

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * ShortToRXString
 */

BOOL ShortToRXString( SHORT val, PRXSTRING str )
  {
    if( !AllocNumSpace( str ) ) goto error;

    str->strlength = sprintf( str->strptr, "%d", val );

    return( TRUE );

  error:
    return( FALSE );
  }

/*
 * RXStringToBoolean -- Sets an RXSTRING to a boolean value ("0" or "1").
 */

BOOL BooleanToRXString( PRXSTRING str, BOOL val )
  {
    if( !AllocNumSpace( str ) ) goto error;

    if( str && str->strptr ){
        strcpy( str->strptr, ( val ? "1" : "0" ) );
        str->strlength = 1;
    }

    return( TRUE );

error:
    return( FALSE );
  }

/*
 * RXStringToBoolean -- Returns 1, 0 or -1 (for error).
 */

BOOL RXStringToBoolean( PRXSTRING str )
  {
    char ch;

    if( !str || !str->strptr || str->strlength == 0 ) goto error;

    if( str->strlength == 1 ){
        ch = str->strptr[0];

        if( ch == '1' || ch == 't' || ch == 'T' ){
            return( 1 );
        } else if( ch == '0' || ch == 'f' || ch == 'F' ){
            return( 0 );
        }
    } else if( str->strlength == 4 &&
               stricmp( str->strptr, "TRUE" ) == 0 ){
        return( 1 );
    } else if( str->strlength == 5 &&
               stricmp( str->strptr, "FALSE" ) == 0 ){
        return( 0 );
    }

  error:
    return( -1 );
  }

#endif
