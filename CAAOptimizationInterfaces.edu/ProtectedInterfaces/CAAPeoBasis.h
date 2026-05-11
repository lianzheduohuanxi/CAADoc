// COPYRIGHT DASSAULT SYSTEMES  2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAPeoBasis
#define ExportedByCAAPeoBasis     __declspec(dllexport)
#else
#define ExportedByCAAPeoBasis     __declspec(dllimport)
#endif
#else
#define ExportedByCAAPeoBasis
#endif
