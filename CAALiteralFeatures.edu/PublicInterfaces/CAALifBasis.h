#ifdef _WINDOWS_SOURCE 
#ifdef __CAALifBasis
#define ExportedByCAALifBasis  __declspec(dllexport) 
#else
#define ExportedByCAALifBasis  __declspec(dllimport) 
#endif
#else
#define ExportedByCAALifBasis
#endif
 
