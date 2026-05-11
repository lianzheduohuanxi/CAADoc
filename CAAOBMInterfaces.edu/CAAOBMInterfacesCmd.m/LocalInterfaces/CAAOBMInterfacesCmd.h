#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAOBMInterfacesCmd
#define ExportedByCAAOBMInterfacesCmd     __declspec(dllexport)
#else
#define ExportedByCAAOBMInterfacesCmd     __declspec(dllimport)
#endif
#else
#define ExportedByCAAOBMInterfacesCmd
#endif
