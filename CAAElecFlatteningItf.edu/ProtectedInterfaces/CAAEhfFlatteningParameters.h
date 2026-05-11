#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAEhfFlatteningParameters
#define ExportedByCAAEhfFlatteningParameters     __declspec(dllexport)
#else
#define ExportedByCAAEhfFlatteningParameters     __declspec(dllimport)
#endif
#else
#define ExportedByCAAEhfFlatteningParameters
#endif
