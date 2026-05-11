#ifdef	_WINDOWS_SOURCE
// COPYRIGHT DASSAULT SYSTEMES 2001
#ifdef	__CAAPstEduNavigExtProv
#define	ExportedByCAAPstEduNavigExtProv	__declspec(dllexport)
#else
#define	ExportedByCAAPstEduNavigExtProv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAPstEduNavigExtProv
#endif



