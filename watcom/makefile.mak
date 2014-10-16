#
#   MAKEFILE.MAK for ezrxfunc.DLL
#

s     = $(%src)
c     = $(s)\c\
h     = $(s)\h\
l     =

hdirs =
ldirs =
model = f

!include ..\watcom\watcinit.mif

libs  = $+$(libs)$-$ rexx clibdl3r os2386

#
# Now define our DLL and OBJ files
#

dllname  = EZRXFUNC
rcname   = EZRXFUNC

dlllnk   = $(dllname).LNK

dlldest  = $(s)\$(dllname).DLL
libdest  = $(s)\$(dllname).LIB


objs     = initterm.obj rxsutils.obj funcload.obj func1.obj func2.obj
exports  = EZLoadFuncs EZDropFuncs EZFunc1 EZFunc2

#
#   Targets
#
all: .symbolic $(dlldest) $(libdest)
    @%null

clean: .symbolic
    -del *.* /n
    -del $(dlldest) /n
    -del $(libdest) /n

#
# Create the import library for the DLL. (You don't really need this
# unless you're also linking to it in C... )
#

$(libdest): $(dlldest)
    wlib /n/b/q $@ +$(dlldest)

$(dlldest): $(objs) $(dlllnk)
    wlink n $(dlldest) @$(dlllnk)
!ifeq ver dbg
    copy /b $(dlldest) + $(dllname).sym $(dlldest)
!endif

#
#   DLL Link File
#

$(dlllnk) : $(s)\watcom\makefile.mak
    %create $@
    @%append $@ system os2v2 dll initinstance terminstance
    @%append $@ option Quiet,Map,CaseExact,ManyAutoData
    @%append $@ option symfile=$(dllname).SYM
    @%append $@ option protmode
    @%append $@ option nodefaultlibs
    @%append $@ option modname=$(dllname)
    @%append $@ debug line
    @for %i in ($(exports)) do @%append $(dlllnk) export %i RESIDENT
    @for %i in ($(objs)) do @%append $(dlllnk) file %i
    @for %i in ($(libs)) do @%append $(dlllnk) library %i

#
# Resources
#

#$(rcname).res: $(s)\$(rcname).rc
#    copy $(s)\$(rcname).rc
#    copy $(s)\*.ico
#    rc -i .. -r $(rcname).rc
#    erase $(rcname).rc
#    erase *.ico

#$(dlldest): $(objs) $(dlllnk) $(rcname).res
#    wlink n $(dlldest)  @$(dlllnk)
#    rc $(rcname).res $(dlldest)
#!ifeq ver dbg
#    copy /b $(dlldest) + $(dllname).sym $(dlldest)
#!endif

