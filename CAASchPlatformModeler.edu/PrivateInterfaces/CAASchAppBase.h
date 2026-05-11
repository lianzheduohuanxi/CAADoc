#ifdef _WINDOWS_SOURCE
#ifdef __CAASchAppBase
#define ExportedByCAASchAppBase  __declspec(dllexport)
#else
#define ExportedByCAASchAppBase __declspec(dllimport)
#endif
#else
#define ExportedByCAASchAppBase
#endif
