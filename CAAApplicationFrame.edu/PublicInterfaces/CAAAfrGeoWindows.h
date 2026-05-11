// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAAfrGeoWindows
#define ExportedByCAAAfrGeoWindows __declspec(dllexport)
#else
#define ExportedByCAAAfrGeoWindows __declspec(dllimport)
#endif
#else
#define ExportedByCAAAfrGeoWindows
#endif
