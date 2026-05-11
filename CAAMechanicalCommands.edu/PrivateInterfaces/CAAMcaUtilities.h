// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAMcaUtilities
#define ExportedByCAAMcaUtilities __declspec(dllexport)
#else
#define ExportedByCAAMcaUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAAMcaUtilities
#endif
