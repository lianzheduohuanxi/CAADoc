#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAPstPrsConfigAddin
#define ExportedByCAAPstPrsConfigAddin     __declspec(dllexport)
#else
#define ExportedByCAAPstPrsConfigAddin     __declspec(dllimport)
#endif
#else
#define ExportedByCAAPstPrsConfigAddin
#endif
