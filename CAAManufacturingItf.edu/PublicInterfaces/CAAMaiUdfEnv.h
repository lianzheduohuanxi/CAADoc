#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMaiUserDefFeatureMapping
#define	ExportedByCAAMaiUdfEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMaiUdfEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMaiUdfEnv
#endif
