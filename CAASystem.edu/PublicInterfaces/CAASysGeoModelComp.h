// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAASysGeoModelComp
#define ExportedByCAASysGeoModelComp __declspec(dllexport)
#else
#define ExportedByCAASysGeoModelComp __declspec(dllimport)
#endif
#else
#define ExportedByCAASysGeoModelComp
#endif
