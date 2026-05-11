#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAMaiProcessTableNewColumn
#define ExportedByCAAMaiProcessTableNewColumn     __declspec(dllexport)
#else
#define ExportedByCAAMaiProcessTableNewColumn     __declspec(dllimport)
#endif
#else
#define ExportedByCAAMaiProcessTableNewColumn
#endif
