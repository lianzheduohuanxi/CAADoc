#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMfgTPEAddToolBar
#define	ExportedByCAAMfgTPEAddToolBar	__declspec(dllexport)
#else
#define	ExportedByCAAMfgTPEAddToolBar	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMfgTPEAddToolBar
#endif
