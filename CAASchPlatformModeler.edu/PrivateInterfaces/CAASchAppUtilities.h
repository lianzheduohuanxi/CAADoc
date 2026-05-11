// COPYRIGHT DASSAULT SYSTEMES 2001

#ifdef _WINDOWS_SOURCE
#ifdef __CAASchAppUtilities
#define ExportedByCAASchAppUtilities __declspec(dllexport)
#else
#define ExportedByCAASchAppUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAASchAppUtilities
#endif
