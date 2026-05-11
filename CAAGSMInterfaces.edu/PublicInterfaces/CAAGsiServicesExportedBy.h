#ifdef _WINDOWS_SOURCE 

#ifdef __CAAGsiServices
#define ExportedByCAAGsiServices    __declspec(dllexport) 
#else 
#define ExportedByCAAGsiServices    __declspec(dllimport) 
#endif 

#else 
#define ExportedByCAAGsiServices
#endif
