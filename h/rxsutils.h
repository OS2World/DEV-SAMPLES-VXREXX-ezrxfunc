/*
 * rxsutils.h -- Useful REXX stuff.
 */

#ifndef RXSUTILS_H_INCLUDED
#define RXSUTILS_H_INCLUDED

    #ifndef STANDARD_H_INCLUDED
    #include "standard.h"
    #endif

    #ifndef REXXSAA_INCLUDED
    #undef  INCL_REXXSAA
    #define INCL_REXXSAA
    #include <rexxsaa.h>
    #endif

    #define  INVALID_ROUTINE 40
    #define  VALID_ROUTINE    0

    extern void SetNullRXString( PRXSTRING str );
    extern void CopyResult( char *src, ULONG len, PRXSTRING dest );

    #ifdef __WATCOMC__

        extern BOOL RXStringToBoolean( PRXSTRING str );
        extern BOOL BooleanToRXString( PRXSTRING str, BOOL val );
        extern BOOL RXStringToULong( PRXSTRING str, PULONG val );
        extern BOOL ULongToRXString( ULONG val, PRXSTRING str );
        extern BOOL RXStringToLong( PRXSTRING str, PLONG val );
        extern BOOL LongToRXString( LONG val, PRXSTRING str );
        extern BOOL RXStringToUShort( PRXSTRING str, PUSHORT val );
        extern BOOL UShortToRXString( USHORT val, PRXSTRING str );
        extern BOOL RXStringToShort( PRXSTRING str, PSHORT val );
        extern BOOL ShortToRXString( SHORT val, PRXSTRING str );

    #endif

#endif
