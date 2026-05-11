#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMfgTPEDisplayToolPathCommand
#define	ExportedByCAAMfgTPEDisplayToolPathCommand	__declspec(dllexport)
#else
#define	ExportedByCAAMfgTPEDisplayToolPathCommand	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMfgTPEDisplayToolPathCommand
#endif
