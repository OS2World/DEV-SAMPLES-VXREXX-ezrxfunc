
============================================================================
EZRXFUNC -- An example of how to build REXX/VX-REXX external functions in C.
----------------------------------------------------------------------------

                                                               Eric Giguere
                                                       WATCOM International
                                                       giguere@watcom.on.ca

============================================================================


Description
-----------

    This package shows you how to write external REXX functions in C and
package them into a DLL.  These functions will then be available for use
by your REXX and VX-REXX programs.  Makefiles are included for use with
WATCOM C 8.5 and up and IBM's C Set/2.

    The information contained herein is not specific to VX-REXX, but if
you want more information on VX-REXX (a visual development environment
for OS/2 that adds Presentation Manager support to your REXX programs),
contact WATCOM (see info at the end of this file).


Installation
------------

From an OS/2 command line, do this:

    WATCOM C:  Run install.cmd, type 'W' and press ENTER.  This copies
               the two files MAKE.CMD and MAKEPROD.CMD from the watcom
               subdirectory.  If your WATCOM environment variable is not
               set, set it now, as in:

                          set WATCOM=c:\watcom

               (Point it to wherever you installed WATCOM C.)  Now type
               'make' to make a debug version of the EZRXFUNC.DLL.  Typing
               'makeprod' makes a production (non-debug) version.  WATCOM
               C 9.5 also assumes you have the TOOLKIT environment variable
               defined.

    C Set/2:   Run install.cmd, type 'C' and press ENTER.  This copies
               the two files MAKE.CMD and MAKEPROD.CMD from the cset
               subdirectory.  Make sure all the appropriate CSET environment
               variables have been set, and that the Toolkit is installed
               and in your path.

If you are running WATCOM C 9.5, you also have to edit the watcom\makefile.mak
file and replace the "clibdl3r" file in the $(LIBS) macro with "clib3r".

Now type 'make' to make a debug version of the EZRXFUNC.DLL.  Typing
'makeprod' makes a production (non-debug) version.

Header files are in the 'h' subdirectory, C files in the 'c' subdirectory,
makefiles and associated junk in either the 'watcom' or 'cset' subdirs.
Object files will be placed in the 'o' and 'oprod' subdirs.


Testing the DLL
---------------

After the make, you will see the file 'EZRXFUNC.DLL' in the current
directory.  You may test the functions in this by typing 'start testdll'.
If you type 'testdll' instead of 'start testdll', you will have to exit
the current OS/2 session to properly unload the DLL.  It is start a new
session and exit it.


How the DLL Works
-----------------

The DLL defines four exported functions that REXX can call.  These functions
are defined using the System calling convention and a fixed number of
arguments.  Take a look at the file func1.c to see an example of this.

To call any of these functions, you must first tell REXX about them.  You
do this using the RXFuncAdd function, as in:

         call RXFuncAdd 'EZLoadFuncs', 'EZRXFUNC', 'EZLoadFuncs'

This tells REXX that when it sees a call to the function 'EZLoadFuncs',
it should load the DLL called 'EZRXFUNC' and call the entry point
called 'EZLoadFuncs'.  The entry point and the function name may be different,
but are often the same.  After this call, you can do this:

         call EZLoadFuncs

and this calls the external function.

It is customary when building an external function DLL to have a function
to automatically register all the other functions in a DLL and a function
to deregister these functions.  By convention, those functions should
be called '<prefix>LoadFuncs' and '<prefix>DropFuncs'.  So after the call
to EZLoadFuncs above, the functions EZFunc1, EZFunc2 and EZFunc3 will
also be available.

Note that when you register a function, it becomes available to _every_
REXX program in the system.  Similarly, if you drop a function it becomes
inaccessible to _every_ REXX program.  You may find it convenient to
register your DLLs in OS/2's STARTUP.CMD file.  You will rarely (usually
never) drop functions.


Building Your Own DLL
---------------------

You can build your own external function DLL based on the skeleton that
EZRXFUNC provides.  The following steps outline the process:

    1. Decide on a name for your DLL, up to 8 characters long.  Say
       you call it 'MYDLL'.  Edit the makefile.mak file for your compiler
       and change the macros that refer to 'EZRXFUNC'.  You must also
       change the module name, which is defined in the makefile for WATCOM C
       and as a separate .DEF file for C Set/2.

    2. Choose a prefix to use for your functions.  It's a good idea to start
       all your functions with the same prefix to prevent name conflicts
       with other external functions.  Say you choose 'My' as the prefix.

    3. Edit the file funcload.c.  Change the functions names for EZLoadFuncs
       and EZDropFuncs to use the new prefix.  Also change the names in the
       table.  Since these names are also exported, you must change the
       exports as well (in the makefile for WATCOM C, in the .DEF file for
       C Set/2).

    4. Write your new functions based on the examples shown in func1.c
       and func2.c.  For each function, add an entry to the table in
       funcload.c and update the exports for the DLL.

    5. If you have special initialization and/or termination issues, you
       can add code to the __dll_initialize and __dll_terminate functions
       in initterm.c.  These functions are called whenever a process loads
       or unloads the DLL.

    6. Note that the DLL is defined so that data segments are nonshared
       and per-process -- in other words, every process that accesses the
       DLL will get its own copy of global & static data, just like
       an executable file.  You can change this if you want.

That's all there is to it...


Notes 
-----

    1. There are two valid return codes for your functions: 0 or 40.  The
       former means everything's OK, and the latter tells REXX to halt
       because of an invalid function call.  If you return 0, always make
       sure you set the result string to something that makes sense, even
       if it's just a null string.

    2. Never try to free the result string pointer that REXX passes you.
       This is a pointer to a fixed-length buffer allocated by the
       interpreter.  If you don't have enough room in that buffer, just
       set the pointer to a new buffer that was allocated with the
       DosAllocMem function.  Take a look at what CopyResult does in
       the rxsutils.c file.

    3. Be prepared for multiple threads.  VX-REXX programs can easily
       run multiple threads of execution, so your REXX function may be
       called simultaneously be two different threads.  Use the usual
       synchronization methods that are available under OS/2 to protect
       global & static data.

    4. Don't modify any of the RXSTRINGs that REXX passes to your function
       except for the result string.

    5. You can register multiple functions with the same entry point. Use
       the "name" argument to distinguish between them.

    6. A bunch of useful utility functions are found in rxsutils.c for
       doing various RXSTRING-to-type conversions.  These functions were
       written for WATCOM C primarily, but will probably compile with C Set
       if you have the migration library installed.  If you want to try
       compiling them with a compiler other than WATCOM's, you must remove
       the #ifdef __WATCOMC__.

    7. What's an RXSTRING?  See the file <rexxsaa.h> for a definition.
       It's just a struct with two fields:  a pointer and a length.  Remember,
       strings in REXX are not null-terminated.  However, the arguments
       that are passed to your function by REXX are null-terminated, so in
       most cases it's OK to use strcmp() and similar functions.  But watch
       out for embedded nulls!


----------------------------------------------------------------------------

North America:                                  Europe:
-------------                                   ------

WATCOM International                            WATCOM Europe
415 Phillip Street                              PO Box 64
Waterloo, Ontario                               Livingston
Canada N2L 3X2                                  West Lothian
                                                EH54 7AE
Toll free in North America: (800) 265-4555      United Kingdom

Phone: (519) 886-3700                           Phone: (44) 506 460112
FAX: (519) 747-4971                             FAX: (44) 506 460115

Email: tech@watcom.on.ca
