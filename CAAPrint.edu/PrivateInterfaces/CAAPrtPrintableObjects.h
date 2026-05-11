#ifdef _WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 1999
// Header used to expose services from the CAAPrtPrintableObjects
// module
//
#if defined(__CAAPrtPrintableObjects)
#define ExportedByCAAPrtPrintableObjects __declspec(dllexport)
#else
#define ExportedByCAAPrtPrintableObjects __declspec(dllimport)
#endif
#else
#define ExportedByCAAPrtPrintableObjects
#endif
