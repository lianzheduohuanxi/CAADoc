#ifdef _WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 1999
// Header used to expose services from the CAASysBBMessage
// module
//
#if defined(__CAASysBBMessageInt)
#define ExportedByCAASysBBMessageInt __declspec(dllexport)
#else
#define ExportedByCAASysBBMessageInt __declspec(dllimport)
#endif
#else
#define ExportedByCAASysBBMessageInt
#endif
