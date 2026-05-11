#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAEhfFlatteningParametersCreate
#define ExportedByCAAEhfFlatteningParametersCreate     __declspec(dllexport)
#else
#define ExportedByCAAEhfFlatteningParametersCreate     __declspec(dllimport)
#endif
#else
#define ExportedByCAAEhfFlatteningParametersCreate
#endif
