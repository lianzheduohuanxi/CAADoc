// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAAfrGeoCreationWbench
#define ExportedByCAAAfrGeoCreationWbench __declspec(dllexport)
#else
#define ExportedByCAAAfrGeoCreationWbench __declspec(dllimport)
#endif
#else
#define ExportedByCAAAfrGeoCreationWbench
#endif
