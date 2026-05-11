// COPYRIGHT DASSAULT SYSTEMES 2003

#ifdef _WINDOWS_SOURCE
#ifdef __CAACloUtilities
#define ExportedByCAACloUtilities __declspec(dllexport)
#else
#define ExportedByCAACloUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAACloUtilities
#endif
