#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAGobAttribute
#define	ExportedByCAAGobAttribute	__declspec(dllexport)
#else
#define	ExportedByCAAGobAttribute	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAGobAttribute
#endif
