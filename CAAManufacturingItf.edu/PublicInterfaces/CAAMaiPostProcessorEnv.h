// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================

#ifdef	_WINDOWS_SOURCE
#ifdef	__CAAMaiUserPostProcessorIntegration
#define	ExportedByCAAMaiPostProcessorEnv	__declspec(dllexport)
#else
#define	ExportedByCAAMaiPostProcessorEnv	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMaiPostProcessorEnv
#endif
