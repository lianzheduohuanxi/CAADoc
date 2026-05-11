#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMaiCreateUserActivityCommand
#define	ExportedByCAAMaiEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMaiEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMaiEnv
#endif
