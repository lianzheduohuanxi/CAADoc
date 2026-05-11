#ifdef	_WINDOWS_SOURCE
// COPYRIGHT DASSAULT SYSTEMES 2000
#ifdef	__CAAOsmManageExtensions
#define	ExportedByCAAOsmManageExtensions	__declspec(dllexport)
#else
#define	ExportedByCAAOsmManageExtensions	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAOsmManageExtensions
#endif


