// COPYRIGHT DASSAULT SYSTEMES 2004
#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMaiCreateUserSetupCommand
#define	ExportedByCAAMaiSetupEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMaiSetupEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMaiSetupEnv
#endif
