#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAEhfGreenLineMechPartAndSupportInBNS
#define ExportedByCAAEhfGreenLineMechPartAndSupportInBNS     __declspec(dllexport)
#else
#define ExportedByCAAEhfGreenLineMechPartAndSupportInBNS     __declspec(dllimport)
#endif
#else
#define ExportedByCAAEhfGreenLineMechPartAndSupportInBNS
#endif
