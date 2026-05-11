// COPYRIGHT DASSAULT SYSTEMES 2003

#ifdef _WINDOWS_SOURCE
#ifdef __CAAArrUtilities
#define ExportedByCAAArrUtilities __declspec(dllexport)
#else
#define ExportedByCAAArrUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAAArrUtilities
#endif
