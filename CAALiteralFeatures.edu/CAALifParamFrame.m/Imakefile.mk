# COPYRIGHT DASSAULT SYSTEMES 1999 - 2000
#======================================================================
# Imakefile for module CAALifParamFrame.m
#======================================================================
#
# LOAD MODULE
#
BUILT_OBJECT_TYPE = LOAD MODULE
MKMFC_DEPENDENCY=Yes 
LINK_WITH = CAALifBasis\
			CATObjectSpecsModeler\
			CATObjectModelerBase \ 
            JS0GROUP DI0PANV2 JS0FM \
						MecModItf KnowledgeItf

OS = Windows_NT 
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

