// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAVisGeoModelInt
#define ExportedByCAAVisGeoModelInt __declspec(dllexport)
#else
#define ExportedByCAAVisGeoModelInt __declspec(dllimport)
#endif
#else
#define ExportedByCAAVisGeoModelInt
#endif
