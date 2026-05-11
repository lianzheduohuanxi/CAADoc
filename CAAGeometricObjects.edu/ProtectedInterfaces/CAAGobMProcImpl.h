// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CAAGobMProcImpl_h
#define CAAGobMProcImpl_h

#ifdef _WINDOWS_SOURCE
# ifdef __CAAGobMProcImpl
#  define ExportedByCAAMProcImpl __declspec(dllexport)
# else
#  define ExportedByCAAMProcImpl __declspec(dllimport)
# endif
#else
# define ExportedByCAAMProcImpl
#endif

ExportedByCAAMProcImpl int CustomGobMProcExample( int iArgc, char** iArgv);

#endif
