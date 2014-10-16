/*
 * install.cmd -- Asks you what kind of compiler you have, then installs
 *                the correct files for you.
 */

main:
    address CMD

    if( DirExists( 'o' ) = 0 )then
      do
        'mkdir o'
      end
    else
      do
        'echo y | del o\*.*'
      end
    
    if( DirExists( 'oprod' ) = 0 )then
      do
        'mkdir oprod'
      end
    else
      do
        'echo y | del oprod\*.*'
      end

    say "Are you using the WATCOM compiler or the CSET/2 compiler?"
    parse pull compiler

    if( left( translate( strip( compiler ) ), 1 ) = 'W' )then
      do
        'copy watcom\*.cmd'
        say ""
        say "Don't forget to set the WATCOM environment variable!"
        say ""
        say "WATCOM C 9.5 users should see the README file for some"
        say "further instructions."
      end
    else
      do
        'copy cset\*.cmd'
      end
    
    exit

/*
 * DirExists -- Returns 1 if the given directory exists.
 */

DirExists: procedure
    dir     = arg(1)
    old_dir = directory()
    exists  = 0

    if( dir <> '' & directory( dir ) <> '' )then
        exists = 1

    call directory old_dir

    return exists

