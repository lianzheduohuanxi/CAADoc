#ifdef	_WINDOWS_SOURCE
// COPYRIGHT DASSAULT SYSTEMES 2001
#ifdef	__CAAPstEduNavigFeatProv
#define	ExportedByCAAPstEduNavigFeatProv	__declspec(dllexport)
#else
#define	ExportedByCAAPstEduNavigFeatProv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAPstEduNavigFeatProv
#endif



