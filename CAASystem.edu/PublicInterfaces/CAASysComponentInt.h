// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAASysComponentInt
#define ExportedByCAASysComponentInt __declspec(dllexport)
#else
#define ExportedByCAASysComponentInt __declspec(dllimport)
#endif
#else
#define ExportedByCAASysComponentInt
#endif
