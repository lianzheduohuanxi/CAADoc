
/* -*-C++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2002
#ifdef	_WINDOWS_SOURCE
#ifdef	__CAACommonFunction
#define	ExportedByCAACommonFunction	__declspec(dllexport)
#else
#define	ExportedByCAACommonFunction	__declspec(dllimport)
#endif
#else
#define	ExportedByCAACommonFunction
#endif
