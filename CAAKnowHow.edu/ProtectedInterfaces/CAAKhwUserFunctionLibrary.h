#ifdef _WINDOWS_SOURCE
#ifdef __CAAKhwUserFunction
#define ExportedByCAAKhwUserFunction  __declspec(dllexport)
#else
#define ExportedByCAAKhwUserFunction  __declspec(dllimport)
#endif
#else
#define ExportedByCAAKhwUserFunction
#endif
