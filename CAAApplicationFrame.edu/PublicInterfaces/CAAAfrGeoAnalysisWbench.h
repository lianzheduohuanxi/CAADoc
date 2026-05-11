// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAAfrGeoAnalysisWbench
#define ExportedByCAAAfrGeoAnalysisWbench __declspec(dllexport)
#else
#define ExportedByCAAAfrGeoAnalysisWbench __declspec(dllimport)
#endif
#else
#define ExportedByCAAAfrGeoAnalysisWbench
#endif
