// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAVisManagerInt
#define ExportedByCAAVisManagerInt __declspec(dllexport)
#else
#define ExportedByCAAVisManagerInt __declspec(dllimport)
#endif
#else
#define ExportedByCAAVisManagerInt
#endif
