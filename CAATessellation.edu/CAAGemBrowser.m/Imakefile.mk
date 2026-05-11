# 
# COPYRIGHT DASSAULT SYSTEMES  2000
#
BUILT_OBJECT_TYPE=LOAD MODULE
MKMFC_DEPENDENCY=Yes
#
OS = COMMON

LINK_WITH = \
  JS0GROUP \
  JS0FM \
  AdvancedMathematics \
  Mathematics \
  CATMathStream \
  CATCGMGeoMath \
            CATGeometricObjects\
  CATTopologicalObjects \
  CATTessellation \
  DI0PANV2 \
  CATVisualization \
  CATViz

OS = AIX
SYS_LIBS = -lXm -lXt -lX11

OS = HP-UX
SYS_LIBS = -lXm -lXt -lX11

OS = IRIX
SYS_LIBS = -lXm -lXt -lX11
LOCAL_CCFLAGS  = -float
LOCAL_CFLAGS   = -float 

OS = SunOS
SYS_LIBS = -lXm -lXt -lX11

OS = Windows_NT
LOCAL_LDFLAGS = $(SUB_WIN)
	
