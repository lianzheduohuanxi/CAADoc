// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAAfrGeometryWshop
#define ExportedByCAAAfrGeometryWshop __declspec(dllexport)
#else
#define ExportedByCAAAfrGeometryWshop __declspec(dllimport)
#endif
#else
#define ExportedByCAAAfrGeometryWshop
#endif
