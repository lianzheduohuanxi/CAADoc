// COPYRIGHT DASSAULT SYSTEMES 2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAPstINFInterfaces
#define ExportedByCAAPstINFInterfaces  __declspec(dllexport)
#else
#define ExportedByCAAPstINFInterfaces  __declspec(dllimport)
#endif
#else
#define ExportedByCAAPstINFInterfaces
#endif
