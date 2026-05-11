// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAASysGeoModelInf
#define ExportedByCAASysGeoModelInf __declspec(dllexport)
#else
#define ExportedByCAASysGeoModelInf __declspec(dllimport)
#endif
#else
#define ExportedByCAASysGeoModelInf
#endif
