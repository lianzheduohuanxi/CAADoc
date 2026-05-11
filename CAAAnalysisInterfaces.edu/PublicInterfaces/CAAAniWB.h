// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
#ifdef _WINDOWS_SOURCE
#ifdef __CAAAniWB
#define ExportedByCAAAniWB __declspec(dllexport)
#else
#define ExportedByCAAAniWB __declspec(dllimport)
#endif
#else
#define ExportedByCAAAniWB
#endif

