// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAVisManagerComp
#define ExportedByCAAVisManagerComp __declspec(dllexport)
#else
#define ExportedByCAAVisManagerComp __declspec(dllimport)
#endif
#else
#define ExportedByCAAVisManagerComp
#endif
