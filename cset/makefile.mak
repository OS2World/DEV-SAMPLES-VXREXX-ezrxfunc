#
# NMAKE-compatible MAKE file
# 

!ifdef DEBUG
copts  = /Ti+ /dDEBUG
lopts  = /DEBUG
!else
copts  = /dNDEBUG /O+ /Gf+ /Gi
lopts  =
!endif

cflags = /Gm+ /Ge- /I..\h /Re /ss /Gd- /Q /C /Se /Kf- /N10 /W2 $(copts)
lflags = /NOLOGO /NOE /NOD /NOI /EXEPACK /PACKCODE /PACKDATA /ALIGN:4 $(lopts)

objs = initterm.obj rxsutils.obj funcload.obj func1.obj func2.obj

cc = icc $(cflags) /Fo$@ $**

all: ..\ezrxfunc.dll

initterm.obj: ..\c\initterm.c
    $(cc)

rxsutils.obj: ..\c\rxsutils.c
    $(cc)

funcload.obj: ..\c\funcload.c
    $(cc)

func1.obj: ..\c\func1.c
    $(cc)

func2.obj: ..\c\func2.c
    $(cc)

..\ezrxfunc.dll: $(objs)
    link386 $(lflags) @..\cset\ezrxfunc.lnk
