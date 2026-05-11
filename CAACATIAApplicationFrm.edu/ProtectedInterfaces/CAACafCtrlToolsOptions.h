// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAACafCtrlToolsOptions
#define ExportedByCAACafCtrlToolsOptions __declspec(dllexport)
#else
#define ExportedByCAACafCtrlToolsOptions __declspec(dllimport)
#endif
#else
#define ExportedByCAACafCtrlToolsOptions
#endif
