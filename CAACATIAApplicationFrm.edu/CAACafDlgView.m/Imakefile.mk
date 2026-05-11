# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAACafDlgView.m
#======================================================================
#
# LOAD MODULE
#
BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH = CATDlgView Mathematics DI0PANV2 JS0GROUP JS0FM VE0BASE

OS = AIX
SYS_LIBS = -lXm -lXt -lX11

OS = HP-UX
SYS_LIBS =  -lXm -lXt -lX11

OS = IRIX
SYS_LIBS = -lXm -lXt -lX11
LOCAL_CCFLAGS  = -float
LOCAL_CFLAGS   = -float 

OS = SunOS
SYS_LIBS = -lXm -lXt -lX11

OS = Windows_NT
MKMFC_DEPENDENCY = yes
LOCAL_LDFLAGS= $(SUB_WIN)
