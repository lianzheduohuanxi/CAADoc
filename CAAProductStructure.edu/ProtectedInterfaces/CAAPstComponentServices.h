#ifdef	_WINDOWS_SOURCE
// COPYRIGHT DASSAULT SYSTEMES 1999
#ifdef	__CAAPstComponentServices
#define	ExportedByCAAPstComponentServices	__declspec(dllexport)
#else
#define	ExportedByCAAPstComponentServices	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAPstComponentServices
#endif


