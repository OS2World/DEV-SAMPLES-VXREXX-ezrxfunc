/*
 * standard.h -- Standard header file to include with every file.  Doesn't
 *               actually include any OS/2 specific stuff.
 */

#ifndef STANDARD_H_INCLUDED
#define STANDARD_H_INCLUDED

    /* Common C headers */
    
    #include <assert.h>    
    #include <ctype.h>    
    #include <string.h>  
    #include <stdio.h>  
    #include <stdlib.h>
    #include <stddef.h>
    
    #define NULLCHAR '\0'
    #define NLCHAR   '\n'
    #define TABCHAR  '\t'
    
    /* Use this to suppress unreferenced variable warnings */
    
    #define place_holder( x )   ((void)x)
    
    #ifndef TRUE
        #define FALSE   0
        #define TRUE    1
    #endif
    
#endif
