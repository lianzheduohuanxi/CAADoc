// COPYRIGHT DASSAULT SYSTEMES 2008

#ifdef _WINDOWS_SOURCE
#ifdef __CAAPspUtilities
#define ExportedByCAAPspUtilities __declspec(dllexport)
#else
#define ExportedByCAAPspUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAAPspUtilities
#endif
