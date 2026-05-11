// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAADegMultiDocCmd
#define ExportedByCAADegMultiDocCmd __declspec(dllexport)
#else
#define ExportedByCAADegMultiDocCmd __declspec(dllimport)
#endif
#else
#define ExportedByCAADegMultiDocCmd
#endif

