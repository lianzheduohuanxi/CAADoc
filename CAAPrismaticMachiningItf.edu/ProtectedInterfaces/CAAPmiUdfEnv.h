#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAPmiUserDefFeatureMappedWithMfgFeature
#define	ExportedByCAAPmiUdfEnv	__declspec(dllexport)
#else
#define	ExportedByCAAPmiUdfEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAPmiUdfEnv
#endif
