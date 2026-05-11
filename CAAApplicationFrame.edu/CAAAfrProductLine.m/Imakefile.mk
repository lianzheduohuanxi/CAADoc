# COPYRIGHT DASSAULT SYSTEMES 2000
#
# LOAD MODULE CAAAfrProductLine
#
BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH = CD0APPLI JS0FM JS0GROUP

OS = AIX
LOCAL_LDFLAGS = -F:xlC_r -bmaxdata:0x40000000
SYS_INCPATH = 
SYS_LIBS = -lc_r -blibpath:/usr/lib/threads:/lib:/usr/lib
SYS_LIBPATH = 

OS = Windows_NT
SYS_LIBS =
MKMFC_DEPENDENCY = yes
LOCAL_LDFLAGS = $(SUB_WIN)

OS = HP-UX
#if os hpux_a
SYS_LIBS = -lcma
# libcma sur HP11 incompatible avec libpthread
#endif

OS = SunOS
SYS_LIBS = -lXm
