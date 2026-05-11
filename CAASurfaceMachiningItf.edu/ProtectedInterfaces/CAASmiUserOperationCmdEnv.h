#ifdef  _WINDOWS_SOURCE
#ifdef  __CAASmiUserOperationCommand
#define ExportedByCAASmiUserOperationCmdEnv     __declspec(dllexport)
#else
#define ExportedByCAASmiUserOperationCmdEnv     __declspec(dllimport)
#endif
#else
#define ExportedByCAASmiUserOperationCmdEnv
#endif
