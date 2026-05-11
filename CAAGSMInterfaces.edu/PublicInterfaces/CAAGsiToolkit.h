// COPYRIGHT DASSAULT SYSTEMES 2000
#ifdef _WINDOWS_SOURCE 
#ifdef __CAAGsiToolkit
#define ExportedByCAAGsiToolkit    __declspec(dllexport) 
#else 
#define ExportedByCAAGsiToolkit   __declspec(dllimport) 
#endif 

#else 
#define ExportedByCAAGsiToolkit 
#endif
