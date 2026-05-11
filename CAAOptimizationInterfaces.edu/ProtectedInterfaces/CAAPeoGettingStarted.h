// COPYRIGHT DASSAULT SYSTEMES  2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAPeoGettingStarted
#define ExportedByCAAPeoGettingStarted     __declspec(dllexport)
#else
#define ExportedByCAAPeoGettingStarted     __declspec(dllimport)
#endif
#else
#define ExportedByCAAPeoGettingStarted
#endif
