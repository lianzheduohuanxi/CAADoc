#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMfgTPESplitToolPathCommand
#define	ExportedByCAAMfgTPESplitToolPathCommand	__declspec(dllexport)
#else
#define	ExportedByCAAMfgTPESplitToolPathCommand	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMfgTPESplitToolPathCommand
#endif
