#ifdef  _WINDOWS_SOURCE
#ifdef  __CAASmiUserMachFeature
#define ExportedByCAASmiUserMachFeatureEnv     __declspec(dllexport)
#else
#define ExportedByCAASmiUserMachFeatureEnv     __declspec(dllimport)
#endif
#else
#define ExportedByCAASmiUserMachFeatureEnv
#endif
