// COPYRIGHT DASSAULT SYSTEMES 2003

#ifdef _WINDOWS_SOURCE
#ifdef __CAASysInterface
#define ExportedByCAASysInterface __declspec(dllexport)
#else
#define ExportedByCAASysInterface __declspec(dllimport)
#endif
#else
#define ExportedByCAASysInterface
#endif
