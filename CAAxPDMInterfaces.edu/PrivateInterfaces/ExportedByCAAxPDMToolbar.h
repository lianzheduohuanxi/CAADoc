// COPYRIGHT DASSAULT SYSTEMES 2006
#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAxPDMToolbar
#define	ExportedByCAAxPDMToolbar	__declspec(dllexport)
#else
#define	ExportedByCAAxPDMToolbar	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAxPDMToolbar
#endif
