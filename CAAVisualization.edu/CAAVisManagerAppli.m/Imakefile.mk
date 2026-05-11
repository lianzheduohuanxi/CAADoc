# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAVisManagerAppli.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = LOAD MODULE

LINK_WITH =  CATVisualization CATViz CAAVisManagerComp CAAVisManagerInt\
             Mathematics \
             DI0PANV2 \
             JS0GROUP JS0FM 

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
