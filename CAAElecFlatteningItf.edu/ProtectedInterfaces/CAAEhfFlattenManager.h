#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAEhfFlattenManager
#define ExportedByCAAEhfFlattenManager     __declspec(dllexport)
#else
#define ExportedByCAAEhfFlattenManager     __declspec(dllimport)
#endif
#else
#define ExportedByCAAEhfFlattenManager
#endif
