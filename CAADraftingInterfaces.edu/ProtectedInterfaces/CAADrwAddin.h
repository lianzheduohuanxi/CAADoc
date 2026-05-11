#ifdef  _WINDOWS_SOURCE
#ifdef  __CAADrwAddin
#define ExportedByCAADrwAddin     __declspec(dllexport)
#else
#define ExportedByCAADrwAddin     __declspec(dllimport)
#endif
#else
#define ExportedByCAADrwAddin
#endif
