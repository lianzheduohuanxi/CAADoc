# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAVisRep.m
#======================================================================
#
# LOAD MODULE
#
BUILT_OBJECT_TYPE = LOAD MODULE

LINK_WITH = CATVisualization CATViz CATMathematics JS0GROUP DI0PANV2 JS0FM

OS = Windows_NT 
MKMFC_DEPENDENCY = yes
LOCAL_LDFLAGS = $(SUB_WIN)

OS = SunOS
SYS_LIBS = -lXm -lXt -lX11

OS = AIX
SYS_LIBS = -lXm -lXt -lX11

OS = HP-UX
SYS_LIBS = -lXm -lXt -lX11

OS = IRIX
SYS_LIBS = -lXm -lXt -lX11
LOCAL_CCFLAGS  = -float
LOCAL_CFLAGS   = -float

