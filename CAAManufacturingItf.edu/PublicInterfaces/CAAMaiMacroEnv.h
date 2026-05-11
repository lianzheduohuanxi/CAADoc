#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMaiMacroAccess
#define	ExportedByCAAMaiMacroEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMaiMacroEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMaiMacroEnv
#endif
