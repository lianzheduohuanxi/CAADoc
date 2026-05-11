#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMfgTPEUserCommandHeaders
#define	ExportedByCAAMfgTPEUserCommandHeadersEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMfgTPEUserCommandHeadersEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMfgTPEUserCommandHeadersEnv
#endif
