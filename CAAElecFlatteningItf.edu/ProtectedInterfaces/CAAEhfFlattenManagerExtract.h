#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAEhfFlattenManagerExtract
#define ExportedByCAAEhfFlattenManagerExtract     __declspec(dllexport)
#else
#define ExportedByCAAEhfFlattenManagerExtract     __declspec(dllimport)
#endif
#else
#define ExportedByCAAEhfFlattenManagerExtract
#endif
