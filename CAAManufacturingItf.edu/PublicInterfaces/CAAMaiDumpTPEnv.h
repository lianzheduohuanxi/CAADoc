//=================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=================================
#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMaiDumpToolPathCommand
#define	ExportedByCAAMaiDumpTPEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMaiDumpTPEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMaiDumpTPEnv
#endif
