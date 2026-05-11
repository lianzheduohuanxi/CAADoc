#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAGobForeign
#define	ExportedByCAAGobForeign	__declspec(dllexport)
#else
#define	ExportedByCAAGobForeign	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAGobForeign
#endif
