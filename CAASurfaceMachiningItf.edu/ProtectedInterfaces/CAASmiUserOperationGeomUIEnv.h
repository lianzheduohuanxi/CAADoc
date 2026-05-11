#ifdef  _WINDOWS_SOURCE
#ifdef  __CAASmiUserOperationGeomUI
#define ExportedByCAASmiUserOperationGeomUIEnv     __declspec(dllexport)
#else
#define ExportedByCAASmiUserOperationGeomUIEnv     __declspec(dllimport)
#endif
#else
#define ExportedByCAASmiUserOperationGeomUIEnv
#endif
