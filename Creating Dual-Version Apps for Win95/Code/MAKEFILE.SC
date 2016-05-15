#
# Makefile for Symantec C/C++ 7.x
#
CC = sc
LN = link
RC = rc
RL = rc

CCFLAGS = /c /ms /WA /DSTRICT
LNFLAGS = /nologo /map
RCFLAGS = /r
RLFLAGS = /31

OBJ_FILES = demo.obj ewv.obj
LIB_FILES = sws.lib libw.lib

all : demo.exe

.cpp.obj :
        $(CC) $(CCFLAGS) $<

ewv.obj : ewv.cpp ewv.h

demo.obj : demo.cpp demo.h ewv.h

demo.bin : $(OBJ_FILES) demo.def
        $(LN) $(LNFLAGS) $(OBJ_FILES),$@,demo.map,$(LIB_FILES),demo.def

demo.res : demo.rc demo.h
        $(RC) $(RCFLAGS) demo.rc

demo.exe : demo.bin demo.res
        @copy demo.bin $@
        $(RL) $(RLFLAGS) demo.res $@

