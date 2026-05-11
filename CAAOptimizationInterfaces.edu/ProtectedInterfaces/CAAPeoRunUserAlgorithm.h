// COPYRIGHT DASSAULT SYSTEMES  2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAPeoRunUserAlgorithm
#define ExportedByCAAPeoRunUserAlgorithm     __declspec(dllexport)
#else
#define ExportedByCAAPeoRunUserAlgorithm     __declspec(dllimport)
#endif
#else
#define ExportedByCAAPeoRunUserAlgorithm
#endif
