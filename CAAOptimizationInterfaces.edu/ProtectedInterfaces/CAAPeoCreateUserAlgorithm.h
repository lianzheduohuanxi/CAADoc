// COPYRIGHT DASSAULT SYSTEMES  2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAPeoCreateUserAlgorithm
#define ExportedByCAAPeoCreateUserAlgorithm     __declspec(dllexport)
#else
#define ExportedByCAAPeoCreateUserAlgorithm     __declspec(dllimport)
#endif
#else
#define ExportedByCAAPeoCreateUserAlgorithm
#endif
